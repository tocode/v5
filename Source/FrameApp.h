#ifndef FRAMEAPP_H
#define FRAMEAPP_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "App.h"
#include "GL.h"
#include "CubeData.h"
#include "Mathematics.h"
#include "Mesh.h"
#include "Pass.h"


class FrameApp: public App
{
public:
	void Initialize()
	{
		gl = MakeGL();
		ProgramPtr pipeline = MakePipeline(gl,cube_vs_src,cube_fs_src);
		pipeline->DeclareAttribute( "POSITION",	"a_position");
		pipeline->DeclareAttribute( "NORMAL",	"a_normal");
		pipeline->DeclareAttribute( "TEXCOOD",	"a_texcood");
		pipeline->DeclareUniform  (	"MVP",		"u_mvp");
		pipeline->DeclareTexture  (	"TEXTURE",	"s_texture");

		TexturePtr texture = MakeTexture(gl,cube_texture,cube_tex_width,cube_tex_height,RGB_FLOAT32);

		pass = MakePass();
		pass->SetProgram(pipeline);
		pass->AttachTexture("TEXTURE",texture);
		pass->Bind(gl);

		VertexBufferPtr positions = MakeVertexBuffer(gl,cube_positions,cube_position_size);
		VertexBufferPtr normals = MakeVertexBuffer(gl,cube_normals,cube_normal_size);
		VertexBufferPtr texcoods = MakeVertexBuffer(gl,cube_texcoods,cube_texcood_size);
		IndexBufferPtr  indices = MakeIndexBuffer(gl,cube_indices,cube_index_size);

		mesh = MakeMesh();
		mesh->AttachInput( "POSITION",  MakeInput(positions,0,12,DF_FLOAT3));
		mesh->AttachInput( "NORMAL",	MakeInput(normals,0,12,DF_FLOAT3));
		mesh->AttachInput( "TEXCOOD",	MakeInput(texcoods,0,8,DF_FLOAT2));
		mesh->SetIndex( MakeIndex(indices,DF_UINT,cube_index_size));
		mesh->SetPrimitiveTopology(PRIMITIVE_TRIANGLES);
		mesh->Bind(gl);
	}
	void Display()
	{
		static int i=0;
		i = (i+1) % 1000;
		float angle = 2*PI*(i/1000.0);
		float aspect = float(glutGet(GLUT_WINDOW_WIDTH)) / glutGet(GLUT_WINDOW_HEIGHT);

		Matrix4 model = Translate(Vector3(0.0, 0.0, -3.0)) * Rotate(Vector3(0.0, 1.0, 0.0),angle);
		Matrix4 view = LookAt(Vector3(0,0,0),Vector3(0,0.3,-1),Vector3(0,1,0));//Identity();
		Matrix4 projection = Perspective(60.0f, aspect, 1.0f, 100.0f);
		Matrix4 mvp = projection * view * model;

		gl->Reset();
		gl->ClearColorBuffer();
		pass->AttachUniform("MVP",MakeUniform(DF_FLOAT4X4,Transpose(mvp)));
		pass->Bind(gl);
		mesh->Bind(gl);
		gl->Draw();
		glutSwapBuffers();
	}
private:
	GLPtr			gl;
	PassPtr			pass;
	MeshPtr			mesh;
};

#endif