#ifndef DOWNSAMPLER_H
#define DOWNSAMPLER_H

#include "GL.h"
#include "TextureFactory.h"
#include "MeshFactory.h"

class DownSampler
{
public:
	void Init(GLPtr gl,float width,float height)
	{
		this->gl = gl;
		this->width = width;
		this->height = height;
		output_tx = MakeTexture(gl,NULL,width/4,height/4,RGBA_FLOAT32);

		string vs_src = GetStrFromFile("downsampler_vs.txt");
		string fs_src = GetStrFromFile("downsampler_fs.txt");

		ProgramPtr program = MakePipeline(gl,vs_src,fs_src);
		program->DeclareAttribute( "POSITION",					"a_position");
		program->DeclareAttribute( "TEXCOOD",					"a_texcood");
		program->DeclareTexture(   "INPUT",						"s_input");
		pass = MakePass();
		pass->SetProgram(program);
		quad = LoadMesh(gl,"quad.obj");
	}
	void Render()
	{
		gl->Reset();
		gl->BindColorBuffer(0,output_tx->TexID());
		gl->ClearColorBuffer(0, 0, 0, 0.0);
		glViewport(0,0,width/4,height/4);
		pass->AttachTexture("INPUT",input_tx);
		pass->Bind(gl);
		quad->Bind(gl);
		gl->Draw();
		glViewport(0,0,width,height);
	}
	void SetInput(TexturePtr input)
	{
		input_tx = input;
	}
	void ShowOutput()
	{
		gl->Reset();

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

		GLuint fb;
		glGenFramebuffers(1,&fb);
		glBindFramebuffer(GL_READ_FRAMEBUFFER,fb);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,output_tx->TexID(),0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glBlitFramebuffer(0,0,width,height,0,0,width*2,height*2,GL_COLOR_BUFFER_BIT,GL_LINEAR);
	}
public:
	GLPtr			gl;
	float			width;
	float			height;
	TexturePtr		input_tx;
	TexturePtr		output_tx;
	PassPtr			pass;
	MeshPtr			quad;
};
DECLARE_POINTER_OF(DownSampler);
DEF_MAKEFUN_OF(DownSampler);





#endif