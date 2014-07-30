#ifndef DEFFEREDLIGHTING_H
#define DEFFEREDLIGHTING_H

#include "GL.h"
#include "TextureFactory.h"
#include "MeshFactory.h"

class DeferredShading
{
public:
	void InitGeometry()
	{
		string deferred_geometry_vs_src = GetStrFromFile("deferred_geometry_vs.txt");
		string deferred_geometry_fs_src = GetStrFromFile("deferred_geometry_fs.txt");

		ProgramPtr program = MakePipeline(gl,deferred_geometry_vs_src,deferred_geometry_fs_src);
		program->DeclareAttribute( "POSITION",					"a_position");
		program->DeclareAttribute( "NORMAL",					"a_normal");
		program->DeclareAttribute( "TEXCOOD",					"a_texcood");
		program->DeclareUniform  (	"WVP",						"u_wvp");
		program->DeclareUniform  ( "WORLD",					"u_world");
		program->DeclareTexture  ( "TEXTURE",                  "s_texture");
		geometry_pass = MakePass();
		geometry_pass->SetProgram(program);

		depth_tx = MakeTexture(gl,NULL,width,height,DEPTH32F_STENCIL8);
		position_tx = MakeTexture(gl,NULL,width,height,RGBA_FLOAT32);
		normal_tx = MakeTexture(gl,NULL,width,height,RGBA_FLOAT32);
		texcood_tx = MakeTexture(gl,NULL,width,height,RGBA_FLOAT32);
		shaded_tx = MakeTexture(gl,NULL,width,height,RGBA_FLOAT32);
	}
	void InitStencil()
	{
		string deferred_stencil_vs_src = GetStrFromFile("deferred_stencil_vs.txt");
		string deferred_stencil_fs_src = GetStrFromFile("deferred_stencil_fs.txt");

		ProgramPtr program = MakePipeline(gl,deferred_stencil_vs_src,deferred_stencil_fs_src);
		program->DeclareAttribute( "POSITION",					"a_position");
		program->DeclareAttribute( "NORMAL",					"a_normal");
		program->DeclareAttribute( "TEXCOOD",					"a_texcood");
		program->DeclareUniform  (	"WVP",						"u_wvp");
		
		stencil_pass = MakePass();
		stencil_pass->SetProgram(program);
	}
	void InitShading()
	{
		sphere = LoadMesh(gl,"sphere.obj");
		quad = LoadMesh(gl,"quad.obj");

		string deferred_point_light_vs_src = GetStrFromFile("deferred_point_light_vs.txt");
		string deferred_point_light_fs_src = GetStrFromFile("deferred_point_light_fs.txt");

		ProgramPtr program = MakePipeline(gl,deferred_point_light_vs_src,deferred_point_light_fs_src);
		program->DeclareAttribute( "POSITION",					"a_position");
		program->DeclareAttribute( "NORMAL",					"a_normal");
		program->DeclareAttribute( "TEXCOOD",					"a_texcood");
		program->DeclareUniform  (	"WVP",						"u_wvp");
		program->DeclareUniform  ( "WORLD",					"u_world");
		program->DeclareUniform  ( "EYE",						"u_eye");
		program->DeclareTexture  (	"TEXTURE",					"s_texture");
		program->DeclareTexture  (	"GBUFFER_POSITION",			"s_position");
		program->DeclareTexture  (	"GBUFFER_NORMAL",			"s_normal");
		program->DeclareTexture  (	"GBUFFER_TEXCOOD",			"s_texcood");

		program->DeclareUniform  ( "DLIGHT_ENABLE",			"dlight_enable");
		program->DeclareUniform  ( "DLIGHT_COLOR",				"dlight.color");
		program->DeclareUniform  ( "DLIGHT_DIRECTION",			"dlight.direction");
		program->DeclareUniform  ( "DLIGHT_AMBIENT_INTENSITY",	"dlight.ambient_intensity");
		program->DeclareUniform  ( "DLIGHT_DIFFUSE_INTENSITY",	"dlight.diffuse_intensity");

		program->DeclareUniform  ( "PLIGHTS_NUM",	"plights_num");
		for (int i=0; i<8; i++)
		{
			program->DeclareUniform(GenStr("PLIGHT%d_COLOR",i),				GenStr("plights[%d].color",i));
			program->DeclareUniform(GenStr("PLIGHT%d_POSITION",i),				GenStr("plights[%d].position",i));
			program->DeclareUniform(GenStr("PLIGHT%d_AMBIENT_INTENSITY",i),	GenStr("plights[%d].ambient_intensity",i));
			program->DeclareUniform(GenStr("PLIGHT%d_DIFFUSE_INTENSITY",i),	GenStr("plights[%d].diffuse_intensity",i));
			program->DeclareUniform(GenStr("PLIGHT%d_CONSTANT_ATTENUATION",i),	GenStr("plights[%d].constant_attenuation",i));
			program->DeclareUniform(GenStr("PLIGHT%d_LINEAR_ATTENUATION",i),	GenStr("plights[%d].linear_attenuation",i));
			program->DeclareUniform(GenStr("PLIGHT%d_EXP_ATTENUATION",i),		GenStr("plights[%d].exp_attenuation",i));	
		}

		program->DeclareUniform  ( "SLIGHTS_NUM",	"slights_num");
		for (int i=0; i<8; i++)
		{
			program->DeclareUniform(GenStr("SLIGHT%d_COLOR",i),				GenStr("slights[%d].color",i));
			program->DeclareUniform(GenStr("SLIGHT%d_POSITION",i),				GenStr("slights[%d].position",i));
			program->DeclareUniform(GenStr("SLIGHT%d_AMBIENT_INTENSITY",i),	GenStr("slights[%d].ambient_intensity",i));
			program->DeclareUniform(GenStr("SLIGHT%d_DIFFUSE_INTENSITY",i),	GenStr("slights[%d].diffuse_intensity",i));
			program->DeclareUniform(GenStr("SLIGHT%d_CONSTANT_ATTENUATION",i),	GenStr("slights[%d].constant_attenuation",i));
			program->DeclareUniform(GenStr("SLIGHT%d_LINEAR_ATTENUATION",i),	GenStr("slights[%d].linear_attenuation",i));
			program->DeclareUniform(GenStr("SLIGHT%d_EXP_ATTENUATION",i),		GenStr("slights[%d].exp_attenuation",i));	
			program->DeclareUniform(GenStr("SLIGHT%d_DIRECTION",i),			GenStr("slights[%d].direction",i));
			program->DeclareUniform(GenStr("SLIGHT%d_CUTOFF",i),				GenStr("slights[%d].cutoff",i));
		}
		plight_pass = MakePass();
		plight_pass->SetProgram(program);

		static int plights_num = 1;
		static Vector3 plight0_color = Vector3(1,1,1);
		plight0_position = Vector3(50,0,-150);
		//plight0_position = Vector3(1,1,1);
		static float plight0_ambient_intensity = 0.3;
		plight0_diffuse_intensity = 0.5;
		static float plight0_constant_attenuation = 0.01;
		static float plight0_linear_attenuation = 0;
		static float plight0_exp_attenuation = 0.0001;
		plight_pass->AttachUniform("PLIGHTS_NUM",MakeUniform(DF_INT,&plights_num));
		plight_pass->AttachUniform("PLIGHT0_COLOR",MakeUniform(DF_FLOAT3,plight0_color));
		plight_pass->AttachUniform("PLIGHT0_POSITION",MakeUniform(DF_FLOAT3,plight0_position));
		plight_pass->AttachUniform("PLIGHT0_AMBIENT_INTENSITY",MakeUniform(DF_FLOAT,&plight0_ambient_intensity));
		plight_pass->AttachUniform("PLIGHT0_DIFFUSE_INTENSITY",MakeUniform(DF_FLOAT,&plight0_diffuse_intensity));
		plight_pass->AttachUniform("PLIGHT0_CONSTANT_ATTENUATION",MakeUniform(DF_FLOAT,&plight0_constant_attenuation));
		plight_pass->AttachUniform("PLIGHT0_LINEAR_ATTENUATION",MakeUniform(DF_FLOAT,&plight0_linear_attenuation));
		plight_pass->AttachUniform("PLIGHT0_EXP_ATTENUATION",MakeUniform(DF_FLOAT,&plight0_exp_attenuation));

	}
	void Init(GLPtr gl,float width,float height)
	{
		this->gl = gl;
		SetScreenSize(width,height);
		InitGeometry();
		InitStencil();
		InitShading();
	}
	void RenderGeometry()
	{
		gl->Reset();

		gl->BindDepthStencilBuffer(depth_tx->TexID());
		gl->BindColorBuffer(0,position_tx->TexID());
		gl->BindColorBuffer(1,normal_tx->TexID());
		gl->BindColorBuffer(2,texcood_tx->TexID());
		
		gl->ClearColorBuffer(0, 0, 0, 0.0);
		gl->ClearDepthBuffer();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		geometry_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,wvp));
		geometry_pass->AttachUniform("WORLD",MakeUniform(DF_FLOAT4X4,w));
		geometry_pass->Bind(gl);
		mesh->Bind(gl);
		
		gl->Draw();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}
	void ShowGBuffer()
	{
		gl->Reset();
	
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

		GLuint fb;
		glGenFramebuffers(1,&fb);
		glBindFramebuffer(GL_READ_FRAMEBUFFER,fb);
		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depth_tx->TexID(),0);
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

	void RenderShading()
	{
		// for each light do this
		{
			float scale = plight0_diffuse_intensity;
			Matrix4 plight0_w = Translate(plight0_position) * Scale(Vector3(180*scale,180*scale,180*scale));
			Matrix4 plight0_wvp = Transpose(vp) * plight0_w;
			Matrix4 plight0_r = Identity();
			plight0_w = Transpose(plight0_w);
			plight0_wvp = Transpose(plight0_wvp);
			plight0_r = Transpose(plight0_r);
			
			// stencil pass
			{
				gl->Reset();

				glEnable(GL_DEPTH_TEST);
				glDepthMask(false);

				glEnable(GL_STENCIL_TEST);

				gl->BindDepthStencilBuffer(depth_tx->TexID());
				gl->ClearStencilBuffer(0);
				glStencilFunc(GL_ALWAYS,0,0);
				glStencilOpSeparate(GL_BACK,GL_KEEP,GL_INCR,GL_KEEP);
				glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_DECR,GL_KEEP);
				
				stencil_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,plight0_wvp));
				stencil_pass->Bind(gl);
				sphere->Bind(gl);
				gl->Draw();

				glDisable(GL_STENCIL_TEST);

				glDepthMask(true);
				glDisable(GL_DEPTH_TEST);
			}

			// light pass
			{
				gl->Reset();

				gl->BindDepthStencilBuffer(depth_tx->TexID());
				gl->BindColorBuffer(0,shaded_tx->TexID());
				gl->ClearColorBuffer(0, 0, 0, 0.0);

				glEnable(GL_BLEND);
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_ONE,GL_ONE);
			
				glDisable(GL_DEPTH_TEST);
				glDepthMask(false);
			
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);

				glEnable(GL_STENCIL_TEST);
				glStencilFunc(GL_NOTEQUAL,0,0xFF);
				glStencilOpSeparate(GL_BACK,GL_KEEP,GL_KEEP,GL_KEEP);
				glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_KEEP);

				plight_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,plight0_wvp));
				plight_pass->AttachUniform("WORLD",MakeUniform(DF_FLOAT4X4,plight0_w));
				plight_pass->AttachTexture("TEXTURE",texture);
				plight_pass->AttachTexture("GBUFFER_POSITION",position_tx);
				plight_pass->AttachTexture("GBUFFER_NORMAL",normal_tx);
				plight_pass->AttachTexture("GBUFFER_TEXCOOD",texcood_tx);
				plight_pass->Bind(gl);
				sphere->Bind(gl);
				gl->Draw();

				glDisable(GL_STENCIL_TEST);

				glCullFace(GL_BACK);
				glDisable(GL_CULL_FACE);

				glDepthMask(true);
				glDisable(GL_DEPTH_TEST);

				glDisable(GL_BLEND);
			}
			
		}
	}
	void ShowShading()
	{
		gl->Reset();

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

		GLuint fb;
		glGenFramebuffers(1,&fb);
		glBindFramebuffer(GL_READ_FRAMEBUFFER,fb);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,shaded_tx->TexID(),0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glBlitFramebuffer(0,0,width,height,width/2,height/2,width,height,GL_COLOR_BUFFER_BIT,GL_LINEAR);
	}
	void Render()
	{
		RenderGeometry();
		ShowGBuffer();
		RenderShading();
		ShowShading();
	}
	void SetScreenSize(float width,float height)
	{
		this->width = width;
		this->height = height;
	}
	void SetMesh(MeshPtr mesh)
	{
		this->mesh = mesh;
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
	PassPtr	geometry_pass;
	PassPtr	stencil_pass;
	PassPtr plight_pass;

	MeshPtr mesh;
	MeshPtr sphere;
	MeshPtr quad;

	TexturePtr depth_tx;
	TexturePtr position_tx;
	TexturePtr normal_tx;
	TexturePtr texcood_tx;
	TexturePtr shaded_tx;

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
DECLARE_POINTER_OF(DeferredShading);
DEF_MAKEFUN_OF(DeferredShading);






#endif