#ifndef SKELETONANIMATIONAPP_H
#define SKELETONANIMATIONAPP_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "App.h"
#include "GL.h"
#include "CubeData.h"
#include "Mathematics.h"
#include "Mesh.h"
#include "Pass.h"
#include "Camera.h"

#include "MeshFactory.h"
#include "TextureFactory.h"
#include "SkeletonAnimationShader.h"

class SkeletonAnimationApp: public App
{
public:
	void Initialize()
	{
		width = glutGet(GLUT_WINDOW_WIDTH);
		height = glutGet(GLUT_WINDOW_HEIGHT);

		gl = MakeGL();
		ProgramPtr pipeline = MakePipeline(gl,SA_vs_src,SA_fs_src);
		pipeline->DeclareAttribute( "POSITION",		"a_position");
		pipeline->DeclareAttribute( "NORMAL",		"a_normal");
		pipeline->DeclareAttribute( "TEXCOOD",		"a_texcood");
		pipeline->DeclareAttribute( "BONEIDS",		"a_bone_ids");
		pipeline->DeclareAttribute( "BONEWEIGHTS",	"a_bone_weights");
		pipeline->DeclareUniform  (	"MVP",			"u_mvp");
		pipeline->DeclareUniform  ( "BONECOUNT",	"u_bone_count");
		pipeline->DeclareUniform  (	"BONEMATRIX",	"u_bone_matrix");
		pipeline->DeclareTexture  (	"TEXTURE",		"s_texture");
		ImagePtr image = LoadImage("guard1_body.png");
		TexturePtr texture = MakeTexture(gl,image->Buffer(),image->Width(),image->Height(),image->Format());

		pass = MakePass();
		pass->SetProgram(pipeline);
		pass->AttachTexture("TEXTURE",texture);

		mesh = LoadMesh(gl,"Bob.md5mesh",true);

		glEnable(GL_DEPTH_TEST);

		camera = MakeCamera(Vector3(0,0,0),Vector3(0,0,-1),Vector3(0,1,0),60,width/height);

		LoadSkeletonAnimation(gl,"Bob.md5mesh",skeleton,animation);
	}
	void Display()
	{
		Matrix4 model = Translate(Vector3(0.0, -40.0, -120.0)) * Rotate(Vector3(0, 1, 0),PI/2) * Rotate(Vector3(0,0,1),PI/2);
		Matrix4 mvp = camera->VPMatrix() * model;

		static float time = 0;
		time += 0.03;
		if (time>animation.duration) time = 0;

		animation.AnimateSkeleton(&skeleton,time);
		bone_matrices = skeleton.GetBoneMatrix();
		bone_matrices_count = bone_matrices.size();

		gl->Reset();
		gl->ClearColorBuffer(0.1,0.3,0.6);
		gl->ClearDepthBuffer();

		pass->AttachUniform("MVP",MakeUniform(DF_FLOAT4X4,Transpose(mvp)));
		pass->AttachUniform("BONECOUNT",MakeUniform(DF_INT,&bone_matrices_count));
		pass->AttachUniform("BONEMATRIX",MakeUniform(DF_FLOAT4X4,&bone_matrices[0],bone_matrices.size()));

		pass->Bind(gl);
		mesh->Bind(gl);
		gl->Draw();
		glutSwapBuffers();
	}
	void KeyDown(int key)
	{
		switch (key)
		{
		case 'w':
			camera->Forward(10);
			break;
		case 's':
			camera->Backward(10);
			break;
		case 'a':
			camera->StrafeLeft(8);
			break;
		case 'd':
			camera->StrafeRight(8);
			break;
		case 27: 
			exit(0); 
			break;
		}
	}
	void MoveTo(int x,int y)
	{
		static int _x=x;
		static int _y=y;
		int dx = x-_x;
		int dy = y-_y;
		camera->Yaw(-dx/width*(60.0/360)*2*PI);
		camera->Pitch(-dy/height*(60.0/360)*2*PI);
		_x=x;
		_y=y;
	}
private:
	GLPtr			gl;
	PassPtr			pass;
	MeshPtr			mesh;
	Skeleton		skeleton;
	Animation		animation;
	CameraPtr		camera;
	float			width;
	float			height;
	vector<Matrix4> bone_matrices;
	int				bone_matrices_count;
};

#endif