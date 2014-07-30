#ifndef CUBEAPP_H
#define CUBEAPP_H

#include "App.h"
#include "GL.h"
#include "CubeData.h"
#include "Mathematics.h"


class CubeApp: public App
{
public:
	void Initialize()
	{
		gl = MakeGL();
		
		/*
		vs = gl->CreateShader(VertexShader,cube_vs_src);
		fs = gl->CreateShader(FragmentShader,cube_fs_src);

		pl = gl->CreateProgram(vs,fs);
		gl->DeclareAttribute( "POSITION", "a_position",  pl);
		gl->DeclareAttribute( "NORMAL",   "a_normal",    pl);
		gl->DeclareAttribute( "TEXCOOD",  "a_texcood",   pl);
		gl->DeclareUniform  ( "MVP",      "u_mvp", pl);
		gl->DeclareTexture  ( "TEXTURE",  "s_texture",   pl);
		gl->BindProgram(pl);
		*/

		ExportedDeclaration export_declaration[5] = {
			{	ET_ATTRIBUTE,	"a_position",	"POSITION"	},
			{	ET_ATTRIBUTE,	"a_normal",	"NORMAL"		},
			{	ET_ATTRIBUTE,	"a_texcood",	"TEXCOOD"	},
			{	ET_UNIFORM,	"u_mvp",		"MVP"		},
			{	ET_TEXTURE,	"s_texture",	"TEXTURE"	}
		};
		
		pl = gl->CreateTheProgram(cube_vs_src,cube_fs_src,export_declaration,5);

		gl->BindProgram(pl);

		positions = gl->CreateVertexBuffer(cube_positions,cube_position_size);
		normals   = gl->CreateVertexBuffer(cube_normals,cube_normal_size);
		texcoods  = gl->CreateVertexBuffer(cube_texcoods,cube_texcood_size);
		indices   = gl->CreateIndexBuffer(cube_indices,cube_index_size);

		gl->BindInput("POSITION",positions,0,12,DF_FLOAT3);
		gl->BindInput("NORMAL",normals,0,12,DF_FLOAT3);
		gl->BindInput("TEXCOOD",texcoods,0,8,DF_FLOAT2);
		gl->BindIndex(indices,DF_UINT,cube_index_size);
		gl->BindPrimitiveTopology(PRIMITIVE_TRIANGLES);

		texture = gl->CreateTexture2D(cube_texture,cube_tex_width,cube_tex_height,RGB_FLOAT32);
		gl->BindTexture("TEXTURE",texture);
	}
	void Display()
	{
		static int i=0;
		i = (i+1) % 1000;
		float angle = 2*PI*(i/1000.0);
		float aspect = float(glutGet(GLUT_WINDOW_WIDTH)) / glutGet(GLUT_WINDOW_HEIGHT);

		Matrix4 model = Translate(Vector3(0.0, 0.0, -3.0)) * Rotate(Vector3(0.0, 1.0, 0.0),angle);
		Matrix4 view = Identity();
		Matrix4 projection = Perspective(60.0f, aspect, 1.0f, 100.0f);
		Matrix4 mvp = projection * view * model;
		
		gl->ClearColorBuffer();
		gl->BindUniform("MVP",DF_FLOAT4X4,Transpose(mvp));
		gl->Draw();
		glutSwapBuffers();
	}
private:
	GLPtr			gl;
	VertexBufferID	positions;
	VertexBufferID	normals;
	VertexBufferID	texcoods;
	IndexBufferID	indices;
	TextureID		texture;
	ShaderID			vs;
	ShaderID			fs;
	ProgramID		pl;
};

#endif