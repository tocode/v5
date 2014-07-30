#ifndef SSAO_H
#define SSAO_H

#include "GL.h"
#include "TextureFactory.h"
#include "MeshFactory.h"

class SSAO
{
public:
	void InitSSAO()
	{
		string ssao_ssao_vs_src = GetStrFromFile("ssao_ssao_vs.txt");
		string ssao_ssao_fs_src = GetStrFromFile("ssao_ssao_fs.txt");

		ProgramPtr program = MakePipeline(gl,ssao_ssao_vs_src,ssao_ssao_fs_src);
		program->DeclareAttribute( "POSITION",					"a_position");
		program->DeclareUniform  ( "WVP",						"u_wvp");
		program->DeclareTexture  ( "GBUFFER_POSITION",			"s_position");
		program->DeclareTexture  ( "GBUFFER_NORMAL",			"s_normal");
		program->DeclareTexture  ( "GBUFFER_TEXCOOD",			"s_texcood");
		ssao_pass = MakePass();
		ssao_pass->SetProgram(program);

		ssao_tx = MakeTexture(gl,NULL,width,height,RGBA_FLOAT32);
		quad = LoadMesh(gl,"quad.obj");
		sphere = LoadMesh(gl,"sphere.obj");
	}
	void Init(GLPtr gl,float width,float height)
	{
		this->gl = gl;
		SetScreenSize(width,height);
		InitSSAO();
	}
	void ShowGBuffer()
	{
		gl->Reset();

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

		GLuint fb;
		glGenFramebuffers(1,&fb);
		glBindFramebuffer(GL_READ_FRAMEBUFFER,fb);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,position_tx->TexID(),0);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,normal_tx->TexID(),0);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_TEXTURE_2D,texcood_tx->TexID(),0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glBlitFramebuffer(0,0,width,height,0,0,width/2,height/2,GL_COLOR_BUFFER_BIT,GL_LINEAR);
		glReadBuffer(GL_COLOR_ATTACHMENT1);
		glBlitFramebuffer(0,0,width,height,width/2,0,width,height/2,GL_COLOR_BUFFER_BIT,GL_LINEAR);
		glReadBuffer(GL_COLOR_ATTACHMENT2);
		glBlitFramebuffer(0,0,width,height,0,height/2,width/2,height,GL_COLOR_BUFFER_BIT,GL_LINEAR);
	}
	void RenderSSAO()
	{
		plight0_diffuse_intensity = 0.5;
		float scale = plight0_diffuse_intensity;
		Matrix4 plight0_w = Translate(plight0_position) * Scale(Vector3(180*scale,180*scale,180*scale));
		Matrix4 plight0_wvp = Transpose(vp) * plight0_w;

		gl->Reset();
		gl->BindColorBuffer(0,ssao_tx->TexID());
		gl->ClearColorBuffer(0, 0, 0, 0.0);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		
		ssao_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,plight0_wvp));
		ssao_pass->AttachTexture("GBUFFER_POSITION",position_tx);
		ssao_pass->AttachTexture("GBUFFER_NORMAL",normal_tx);
		ssao_pass->AttachTexture("GBUFFER_TEXCOOD",texcood_tx);
		ssao_pass->Bind(gl);
		sphere->Bind(gl);
		gl->Draw();
		
		//glDisable(GL_CULL_FACE);
	}
	void ShowSSAO()
	{
		gl->Reset();

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

		GLuint fb;
		glGenFramebuffers(1,&fb);
		glBindFramebuffer(GL_READ_FRAMEBUFFER,fb);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,ssao_tx->TexID(),0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glBlitFramebuffer(0,0,width,height,0,0,width/2,height/2,GL_COLOR_BUFFER_BIT,GL_LINEAR);
	}
	void Render()
	{
		ShowGBuffer();
		RenderSSAO();
		ShowSSAO();
	}
	void SetScreenSize(float width,float height)
	{
		this->width = width;
		this->height = height;
	}
	void SetTexture(TexturePtr texture)
	{
		this->texture = texture;
	}
	void SetWVP(Matrix4 wvp)
	{
		this->wvp = Transpose(wvp);
	}
	void SetVP(Matrix4 vp)
	{
		this->vp = Transpose(vp);
	}
	void SetW(Matrix4 w)
	{
		this->w = Transpose(w);
	}
public:
	GLPtr	gl;
	PassPtr ssao_pass;

	MeshPtr sphere;
	MeshPtr quad;

	TexturePtr depth_tx;
	TexturePtr position_tx;
	TexturePtr normal_tx;
	TexturePtr texcood_tx;
	TexturePtr ssao_tx;

	TexturePtr texture;
	float width;
	float height;
	Matrix4 wvp;
	Matrix4 vp;
	Matrix4 w;

	FrameBufferID fb;

	Vector3 plight0_position;
	float plight0_diffuse_intensity;
};
DECLARE_POINTER_OF(SSAO);
DEF_MAKEFUN_OF(SSAO);






#endif