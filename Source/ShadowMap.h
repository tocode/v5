#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "GL.h"
#include "TextureFactory.h"
#include "MeshFactory.h"

class ShadowMap
{
public:
	void InitZPass(GLPtr gl)
	{
		string zpass_vs_src = GetStrFromFile("shadowmap_zpass_vs.txt");
		string zpass_fs_src = GetStrFromFile("shadowmap_zpass_fs.txt");

		ProgramPtr program = MakePipeline(gl,zpass_vs_src,zpass_fs_src);
		program->DeclareAttribute( "POSITION",	"a_position" );
		program->DeclareUniform  (	"WVP",		"u_wvp" );

		z_pass = MakePass();
		z_pass->SetProgram(program);

		depth_tx = MakeTexture(gl,NULL,width,height,DEPTH32);
	}
	void InitShowZPass(GLPtr gl)
	{
		string showz_vs_src = GetStrFromFile("shadowmap_showz_vs.txt");
		string showz_fs_src = GetStrFromFile("shadowmap_showz_fs.txt");

		ProgramPtr program = MakePipeline(gl,showz_vs_src,showz_fs_src);
		program->DeclareAttribute( "POSITION",	"a_position" );
		program->DeclareAttribute( "TEXCOOD",	"a_texcood" );
		program->DeclareUniform  (	"WVP",		"u_wvp" );
		program->DeclareTexture  ( "TEXTURE",  "s_texture" );

		showz_pass = MakePass();
		showz_pass->SetProgram(program);
		showz_pass->AttachTexture("TEXTURE",depth_tx);

		quad = LoadMesh(gl,"quad.obj");
	}
	void InitMappingPass(GLPtr gl)
	{
		string mapping_vs_src = GetStrFromFile("shadowmap_mapping_vs.txt");
		string mapping_fs_src = GetStrFromFile("shadowmap_mapping_fs.txt");

		ProgramPtr program = MakePipeline(gl,mapping_vs_src,mapping_fs_src);
		program->DeclareAttribute( "POSITION",	 "a_position" );
		program->DeclareAttribute( "NORMAL",    "a_normal" );
		program->DeclareAttribute( "TEXCOOD",	 "a_texcood" );
		program->DeclareUniform  (	"WVP",		 "u_wvp" );
		program->DeclareUniform  ( "WORLD",     "u_world" );
		program->DeclareUniform  ( "LIGHT_WVP", "u_light_wvp" );
		program->DeclareTexture  ( "SHADOWMAP", "s_shadowmap" );
		program->DeclareTexture  ( "TEXTURE",   "s_texture" );

		mapping_pass = MakePass();
		mapping_pass->SetProgram(program);

		quad = LoadMesh(gl,"quad.obj");
	}
	void Init(GLPtr gl,float width,float height)
	{
		this->gl = gl;
		this->width = width;
		this->height = height;

		
		InitZPass(gl);
		InitShowZPass(gl);
		InitMappingPass(gl);
	}
	void RenderZPass()
	{
		Matrix4 _light_wvp = light_camera->VPMatrix() * world;
		gl->Reset();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		gl->BindDepthStencilBuffer(depth_tx->TexID());
		gl->ClearColorBuffer();
		gl->ClearDepthBuffer();
		z_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,Transpose(_light_wvp)));
		z_pass->Bind(gl);
		mesh->Bind(gl);
		gl->Draw();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}
	void RenderShowZPass()
	{
		CameraPtr _camera = MakeCamera(Vector3(0,0,0),Vector3(0,0,-1),Vector3(0,1,0),60,width/height);
		Matrix4 _world = Translate(Vector3(0.0, 0.0, -10)) * Scale(Vector3(4,3,1));
		Matrix4 _wvp = _camera->VPMatrix() * _world;

		gl->Reset();
		gl->ClearColorBuffer(0.2,0.2,0.2);
		showz_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,Transpose(_wvp)));
		showz_pass->AttachTexture("TEXTURE",depth_tx);
		showz_pass->Bind(gl);
		quad->Bind(gl);
		gl->Draw();
	}
	void RenderMappingPass()
	{
		Matrix4 light_wvp = light_camera->VPMatrix() * world;
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		gl->Reset();
		gl->ClearColorBuffer(0.2,0.2,0.2);
		gl->ClearDepthBuffer();
		mapping_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,Transpose(wvp)));
		mapping_pass->AttachUniform("WORLD",MakeUniform(DF_FLOAT4X4,Transpose(world)));
		mapping_pass->AttachUniform("LIGHT_WVP",MakeUniform(DF_FLOAT4X4,Transpose(light_wvp)));
		mapping_pass->AttachTexture("SHADOWMAP",depth_tx);
		mapping_pass->Bind(gl);
		mesh->Bind(gl);
		gl->Draw();

		Matrix4 quad_world = Translate(Vector3(0.0, -50.0, -150)) * Rotate(Vector3(1,0,0),PI/2) * Scale(Vector3(60,60,60));
		Matrix4 quad_wvp = vp * quad_world;
		Matrix4 _light_wvp = light_camera->VPMatrix() * quad_world;
		mapping_pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,Transpose(quad_wvp)));
		mapping_pass->AttachUniform("WORLD",MakeUniform(DF_FLOAT4X4,Transpose(quad_world)));
		mapping_pass->AttachUniform("LIGHT_WVP",MakeUniform(DF_FLOAT4X4,Transpose(_light_wvp)));
		mapping_pass->AttachTexture("SHADOWMAP",depth_tx);
		mapping_pass->Bind(gl);
		quad->Bind(gl);
		gl->Draw();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}
	void Render()
	{
		Vector3 light_to_object = Vector3(0,-30,-150) - light_pos;
		light_camera = MakeCamera(light_pos,light_to_object,Vector3(0,1,0),60,width/height,1,300);
		RenderZPass();
		RenderShowZPass();
		RenderMappingPass();
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
		this->wvp = wvp;
	}
	void SetW(Matrix4 w)
	{
		this->world = w;
	}
	void SetEye(Vector3 eye)
	{
		this->eye = eye;
	}
	void SetLightPos(Vector3 pos)
	{
		this->light_pos = pos;
	}
	void SetVP(Matrix4 vp)
	{
		this->vp = vp;
	}
public:
	GLPtr				gl;
	PassPtr				z_pass;
	PassPtr				showz_pass;
	PassPtr				mapping_pass;
	MeshPtr				mesh;
	MeshPtr				quad;
	TexturePtr			depth_tx;
	Matrix4				wvp;
	Matrix4				vp;
	Matrix4				world;
	Vector3				eye;
	float				width;
	float				height;
	TexturePtr			texture;

	Vector3				light_pos;
	CameraPtr			light_camera;
};
DECLARE_POINTER_OF(ShadowMap);
DEF_MAKEFUN_OF(ShadowMap);


#endif