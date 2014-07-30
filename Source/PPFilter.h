#ifndef PPFILTER_H
#define PPFILTER_H

#include "GL.h"
#include "TextureFactory.h"
#include "MeshFactory.h"

class PPFilter
{
public:
	void Init(GLPtr gl,float width,float height)
	{
		this->gl = gl;
		this->width = width;
		this->height = height;
		output = MakeTexture(gl,NULL,width,height,RGBA_FLOAT32);
		
		string vs_src = GetStrFromFile(".txt");
		string fs_src = GetStrFromFile(".txt");

		ProgramPtr program = MakePipeline(gl,vs_src,fs_src);
		program->DeclareAttribute( "POSITION",					"a_position");
		program->DeclareUniform  ( "WVP",						"u_wvp");
		program->DeclareTexture  ( "GBUFFER_POSITION",			"s_position");
		program->DeclareTexture  ( "GBUFFER_NORMAL",			"s_normal");
		program->DeclareTexture  ( "GBUFFER_TEXCOOD",			"s_texcood");
		pass = MakePass();
		pass->SetProgram(program);
	}
	void Render()
	{
		gl->Reset();
		gl->BindColorBuffer(0,output->TexID());
		gl->ClearColorBuffer(0, 0, 0, 0.0);

		gl->Draw();
	}
	void SetInput(TexturePtr input)
	{
		this->input = input;
	}
public:
	GLPtr			gl;
	float			width;
	float			height;
	TexturePtr		input;
	TexturePtr		output;
	PassPtr			pass;
};





#endif