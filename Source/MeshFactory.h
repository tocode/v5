#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include <vector>

#include "GL.h"
#include "mesh.h"
#include "Mathematics.h"

#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags

#include "SkeletonAnimation.h"

MeshPtr LoadMesh(GLPtr gl, std::string filename, bool convert_v=false)
{
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if (!pScene) 
		printf("Error parsing '%s': '%s'\n", filename.c_str(), Importer.GetErrorString()), exit(0); 

	std::vector<MeshPtr> meshes;

	for (unsigned int k = 0 ; k < pScene->mNumMeshes ; k++) 
	{
		const aiMesh* paiMesh = pScene->mMeshes[k];
		
		//int idx = paiMesh->mMaterialIndex;
		//aiMaterial* mt = pScene->mMaterials[idx];
	
		//for (int i=0; i<mt->mNumProperties; i++)
		//	printf("%s %d %d %s\n",mt->mProperties[i]->mKey.data,mt->mProperties[i]->mDataLength,mt->mProperties[i]->mData,mt->mProperties[i]->mData+4);

		std::vector<aiVector3D> positions;
		std::vector<aiVector3D> normals;
		std::vector<aiVector2D> texcoods;
		for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) 
		{
			if (paiMesh->HasPositions())
				positions.push_back(paiMesh->mVertices[i]);

			if (paiMesh->HasNormals())
				normals.push_back(paiMesh->mNormals[i]);

			if (paiMesh->HasTextureCoords(0))
				texcoods.push_back(aiVector2D( paiMesh->mTextureCoords[0][i].x, (convert_v)?(1-paiMesh->mTextureCoords[0][i].y):paiMesh->mTextureCoords[0][i].y ) );
			else
				texcoods.push_back(aiVector2D());
		}

		typedef vector<float> JointIDs;
		typedef vector<float> JointWeights;
		vector<JointIDs> JointIDsPerVertex(paiMesh->mNumVertices);
		vector<JointWeights> JointWeightsPerVertex(paiMesh->mNumVertices);
		for( unsigned int i = 0; i < paiMesh->mNumBones; i++)	{
			const aiBone* bone = paiMesh->mBones[i];
			for( unsigned int j = 0; j < bone->mNumWeights; j++)
			{
				JointIDsPerVertex[bone->mWeights[j].mVertexId].push_back(i);
				JointWeightsPerVertex[bone->mWeights[j].mVertexId].push_back(bone->mWeights[j].mWeight);
			}
		}
		for (int i=0; i<paiMesh->mNumVertices; i++)
		{
			for (int j=JointIDsPerVertex[i].size(); j<4; j++)
				JointIDsPerVertex[i].push_back(0);
			for (int j=JointWeightsPerVertex[i].size(); j<4; j++)
				JointWeightsPerVertex[i].push_back(0);
		}

		float* joint_ids_buf = new float[JointIDsPerVertex.size()*4];
		float* joint_weights_buf = new float[JointWeightsPerVertex.size()*4];
		float* p1 = joint_ids_buf;
		float* p2 = joint_weights_buf;
		for (int i=0; i<JointIDsPerVertex.size(); i++)
			for (int j=0; j<JointIDsPerVertex[i].size(); j++)
				*p1++ = JointIDsPerVertex[i][j];
		for (int i=0; i<JointWeightsPerVertex.size(); i++)
			for (int j=0; j<JointWeightsPerVertex[i].size(); j++)
				*p2++ = JointWeightsPerVertex[i][j];
		

		std::vector<unsigned int> indices;
		for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) 
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			indices.push_back(Face.mIndices[0]);
			indices.push_back(Face.mIndices[1]);
			indices.push_back(Face.mIndices[2]);
		}

		MeshPtr mesh = MakeMesh();
		mesh->AttachInput("POSITION",MakeInput(MakeVertexBuffer(gl,&positions[0],positions.size()*sizeof(aiVector3D)),0,sizeof(aiVector3D),DF_FLOAT3));
		mesh->AttachInput("NORMAL",MakeInput(MakeVertexBuffer(gl,&normals[0],normals.size()*sizeof(aiVector3D)),0,sizeof(aiVector3D),DF_FLOAT3));
		mesh->AttachInput("TEXCOOD",MakeInput(MakeVertexBuffer(gl,&texcoods[0],texcoods.size()*sizeof(aiVector2D)),0,sizeof(aiVector2D),DF_FLOAT2));
		mesh->AttachInput("BONEIDS",MakeInput(MakeVertexBuffer(gl,joint_ids_buf,JointIDsPerVertex.size()*4*sizeof(float)),0,4*sizeof(float),DF_FLOAT4));
		mesh->AttachInput("BONEWEIGHTS",MakeInput(MakeVertexBuffer(gl,joint_weights_buf,JointWeightsPerVertex.size()*4*sizeof(float)),0,4*sizeof(float),DF_FLOAT4));
		mesh->SetIndex(MakeIndex(MakeIndexBuffer(gl,&indices[0],indices.size()*sizeof(unsigned int)),DF_UINT,indices.size()));
		mesh->SetPrimitiveTopology(PRIMITIVE_TRIANGLES);
		meshes.push_back(mesh);
	}
	
	assert(meshes.size()>0);
	return meshes[0];
}
void UpdateNodeByNameFrom(aiNode* node,map<string,aiNode*>& node_by_name)
{
	node_by_name[node->mName.data]=node;
	for (int i=0; i<node->mNumChildren; i++)
		UpdateNodeByNameFrom(node->mChildren[i],node_by_name);
}
Skeleton LoadSkeleton2(const aiScene* scene,const aiMesh* mesh)
{
	map<string,aiNode*> node_by_name;
	UpdateNodeByNameFrom(scene->mRootNode,node_by_name);

	Skeleton skeleton;
	skeleton.joints.resize(mesh->mNumBones);
	
	for (int i=0; i<mesh->mNumBones; i++)
	{
		string name = mesh->mBones[i]->mName.data;
		aiNode* node = node_by_name[name];
		Joint* joint = new Joint;
		joint->name = name;
		joint->offset = Matrix4((float*)&(mesh->mBones[i]->mOffsetMatrix));
		joint->local = Matrix4((float*)&(node_by_name[name]->mTransformation));
		skeleton.joints[i] = joint;
		skeleton.joint_by_name[name] = joint;
	}
	for (int i=0; i<mesh->mNumBones; i++)
	{
		string name = mesh->mBones[i]->mName.data;
		aiNode* node = node_by_name[name];
		if ( skeleton.joint_by_name.find(node->mParent->mName.data) != skeleton.joint_by_name.end() )
			skeleton.joints[i]->father = skeleton.joint_by_name[node->mParent->mName.data];
		else
		{
			skeleton.joints[i]->father = NULL;
			skeleton.root = skeleton.joints[i];
		}

		for (int j=0; j<node->mNumChildren; j++)
			if ( skeleton.joint_by_name.find(node->mChildren[j]->mName.data) != skeleton.joint_by_name.end() )
				skeleton.joints[i]->children.push_back(skeleton.joint_by_name[node->mChildren[j]->mName.data]);
	}
	return skeleton;
}
Animation LoadAnimation(const aiAnimation* anim)
{
	Animation animation;
	float tick_per_second = (anim->mTicksPerSecond)?(anim->mTicksPerSecond):1;
	animation.duration = anim->mDuration/tick_per_second;

	for( unsigned int a = 0; a < anim->mNumChannels; a++)
	{
		const aiNodeAnim* chan = anim->mChannels[a];
		
		Channel channel;
		channel.joint_name = chan->mNodeName.data;
		
		for (int i=0; i<chan->mNumPositionKeys; i++)
			channel.position_frames.push_back(PositionFrame(chan->mPositionKeys[i].mTime/tick_per_second,Vector3((float*)&(chan->mPositionKeys[i].mValue))));

		for (int i=0; i<chan->mNumScalingKeys; i++)
			channel.scale_frames.push_back(ScaleFrame(chan->mScalingKeys[i].mTime/tick_per_second,Vector3((float*)&(chan->mScalingKeys[i].mValue))));
		
		for (int i=0; i<chan->mNumRotationKeys; i++)
		{
			aiQuaternion aiQ = chan->mRotationKeys[i].mValue;
			channel.rotation_frames.push_back(RotationFrame(chan->mRotationKeys[i].mTime/tick_per_second,Quaternion(aiQ.w,aiQ.x,aiQ.y,aiQ.z)));
		}
		animation.channels.push_back(channel);
	}
	return animation;
}
void LoadSkeletonAnimation(GLPtr gl,std::string filename,Skeleton& skeleton,Animation& animation)
{
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs );//| aiProcess_ConvertToLeftHanded);

	if (!pScene) 
		printf("Error parsing '%s': '%s'\n", filename.c_str(), Importer.GetErrorString()), exit(0); 
	
	//Skeleton skeleton;
	//for (int k=0; k<pScene->mNumMeshes; k++)
	{
		int k=0;
		if (pScene->mMeshes[k]->HasBones())
			 skeleton = LoadSkeleton2(pScene,pScene->mMeshes[k]);
	}

	animation = LoadAnimation(pScene->mAnimations[0]);
}



#endif