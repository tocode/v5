#ifndef FORWARDLIGHTING_H
#define FORWARDLIGHTING_H

#include "GL.h"
#include "TextureFactory.h"
#include "MeshFactory.h"


class ForwardLighting
{
public:
	void Init(GLPtr gl)
	{
		this->gl = gl;
		
		string forward_vs_src =	GetStrFromFile("forward_vs.txt");
		string forward_fs_src = GetStrFromFile("forward_fs.txt");
		
		ProgramPtr program = MakePipeline(gl,forward_vs_src,forward_fs_src);
		program->DeclareAttribute( "POSITION",					"a_position");
		program->DeclareAttribute( "NORMAL",					"a_normal");
		program->DeclareAttribute( "TEXCOOD",					"a_texcood");
		program->DeclareUniform  (	"WVP",						"u_wvp");
		program->DeclareUniform  ( "WORLD",					"u_world");
		program->DeclareUniform  ( "EYE",						"u_eye");
		program->DeclareTexture  (	"TEXTURE",					"s_texture");

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

		pass = MakePass();
		pass->SetProgram(program);
		static int dlight_enable = 1;
		static Vector3 dlight_color = Vector3(1,1,1);
		static Vector3 dlight_direction = Vector3(0,-1,0);
		static float dlight_ambient_intensity = 0.4;
		static float dlight_diffuse_intensity = 0.4;
		pass->AttachUniform("DLIGHT_ENABLE",MakeUniform(DF_INT,&dlight_enable));
		pass->AttachUniform("DLIGHT_COLOR",MakeUniform(DF_FLOAT3,dlight_color));
		pass->AttachUniform("DLIGHT_DIRECTION",MakeUniform(DF_FLOAT3,dlight_direction));
		pass->AttachUniform("DLIGHT_AMBIENT_INTENSITY",MakeUniform(DF_FLOAT,&dlight_ambient_intensity));
		pass->AttachUniform("DLIGHT_DIFFUSE_INTENSITY",MakeUniform(DF_FLOAT,&dlight_diffuse_intensity));
		
		static int plights_num = 1;
		static Vector3 plight0_color = Vector3(1,1,1);
		static Vector3 plight0_position = Vector3(50,-50,-150);
		static float plight0_ambient_intensity = 0.3;
		static float plight0_diffuse_intensity = 0.5;
		static float plight0_constant_attenuation = 0.1;
		static float plight0_linear_attenuation = 0.01;
		static float plight0_exp_attenuation = 0.0;
		pass->AttachUniform("PLIGHTS_NUM",MakeUniform(DF_INT,&plights_num));
		pass->AttachUniform("PLIGHT0_COLOR",MakeUniform(DF_FLOAT3,plight0_color));
		pass->AttachUniform("PLIGHT0_POSITION",MakeUniform(DF_FLOAT3,plight0_position));
		pass->AttachUniform("PLIGHT0_AMBIENT_INTENSITY",MakeUniform(DF_FLOAT,&plight0_ambient_intensity));
		pass->AttachUniform("PLIGHT0_DIFFUSE_INTENSITY",MakeUniform(DF_FLOAT,&plight0_diffuse_intensity));
		pass->AttachUniform("PLIGHT0_CONSTANT_ATTENUATION",MakeUniform(DF_FLOAT,&plight0_constant_attenuation));
		pass->AttachUniform("PLIGHT0_LINEAR_ATTENUATION",MakeUniform(DF_FLOAT,&plight0_linear_attenuation));
		pass->AttachUniform("PLIGHT0_EXP_ATTENUATION",MakeUniform(DF_FLOAT,&plight0_exp_attenuation));

		static int slights_num = 1;
		static Vector3 slight0_color = Vector3(1,1,1);
		static Vector3 slight0_position = Vector3(50,-50,-150);
		static float slight0_ambient_intensity = 0.3;
		static float slight0_diffuse_intensity = 0.5;
		static float slight0_constant_attenuation = 0.1;
		static float slight0_linear_attenuation = 0.01;
		static float slight0_exp_attenuation = 0.0;
		static Vector3 slight0_direction = Vector3(0,1,0);
		static float slight0_cutoff = PI/4;
		pass->AttachUniform("SLIGHTS_NUM",MakeUniform(DF_INT,&slights_num));
		pass->AttachUniform("SLIGHT0_COLOR",MakeUniform(DF_FLOAT3,slight0_color));
		pass->AttachUniform("SLIGHT0_POSITION",MakeUniform(DF_FLOAT3,slight0_position));
		pass->AttachUniform("SLIGHT0_AMBIENT_INTENSITY",MakeUniform(DF_FLOAT,&slight0_ambient_intensity));
		pass->AttachUniform("SLIGHT0_DIFFUSE_INTENSITY",MakeUniform(DF_FLOAT,&slight0_diffuse_intensity));
		pass->AttachUniform("SLIGHT0_CONSTANT_ATTENUATION",MakeUniform(DF_FLOAT,&slight0_constant_attenuation));
		pass->AttachUniform("SLIGHT0_LINEAR_ATTENUATION",MakeUniform(DF_FLOAT,&slight0_linear_attenuation));
		pass->AttachUniform("SLIGHT0_EXP_ATTENUATION",MakeUniform(DF_FLOAT,&slight0_exp_attenuation));
		pass->AttachUniform("SLIGHT0_DIRECTION",MakeUniform(DF_FLOAT3,slight0_direction));
		pass->AttachUniform("SLIGHT0_CUTOFF",MakeUniform(DF_FLOAT,&slight0_cutoff));
	}
	void Render()
	{
		gl->Reset();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,wvp));
		pass->AttachUniform("WORLD",MakeUniform(DF_FLOAT4X4,w));
		pass->AttachUniform("EYE",MakeUniform(DF_FLOAT3,eye));
		pass->Bind(gl);
		mesh->Bind(gl);
		gl->Draw();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}
	void SetMesh(MeshPtr mesh)
	{
		this->mesh = mesh;
	}
	void SetTexture(TexturePtr texture)
	{
		pass->AttachTexture("TEXTURE",texture);
	}
	void SetWVP(Matrix4 wvp)
	{
		this->wvp = Transpose(wvp);
	}
	void SetW(Matrix4 w)
	{
		this->w = Transpose(w);
	}
	void SetEye(Vector3 eye)
	{
		this->eye = eye;
	}
public:
	GLPtr gl;
	PassPtr pass;
	MeshPtr mesh;
	Matrix4 wvp;
	Matrix4 w;
	Vector3	eye;
};
DECLARE_POINTER_OF(ForwardLighting);
DEF_MAKEFUN_OF(ForwardLighting);


#endif