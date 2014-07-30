#ifndef SKYBOX_H
#define SKYBOX_H

#include "GL.h"
#include "TextureFactory.h"
#include "MeshFactory.h"

class SkyBox
{
public:
	void Init(GLPtr gl)
	{
		this->gl = gl;
		string skybox_vs_src =	
			"attribute vec3 a_position;										\n"
			"uniform mat4 u_WVP;											\n"
			"varying vec3 v_cube_texcood;									\n"
			"void main()													\n"
			"{																\n"
			"	vec4 WVP_Pos = u_WVP * vec4(a_position, 1.0);				\n"
			"	gl_Position = WVP_Pos.xyww;									\n"
			"	v_cube_texcood = a_position;								\n"
			"}																\n";
		
		string skybox_fs_src = 
			"attribute vec3 v_cube_texcood;									\n"
			"uniform samplerCube s_texture;									\n"
			"void main()													\n"
			"{																\n"
			"	gl_FragColor = texture(s_texture,v_cube_texcood);			\n"
			"}																\n";
		ProgramPtr pipeline = MakePipeline(gl,skybox_vs_src,skybox_fs_src);
		pipeline->DeclareAttribute( "POSITION",		"a_position");
		pipeline->DeclareUniform  (	"WVP",			"u_WVP");
		pipeline->DeclareTexture  (	"TEXTURE",		"s_texture");

		ImagePtr front = LoadImage("sp3front.jpg");
		ImagePtr back = LoadImage("sp3back.jpg");
		ImagePtr left = LoadImage("sp3left.jpg");
		ImagePtr right = LoadImage("sp3right.jpg");
		ImagePtr top = LoadImage("sp3top.jpg");
		ImagePtr bot = LoadImage("sp3bot.jpg");
		front->Flip();
		back->Flip();
		left->Flip();
		right->Flip();
		top->Flip();
		bot->Flip();
		void* buffers[] = { right->Buffer(), left->Buffer(), top->Buffer(), bot->Buffer(), front->Buffer(), back->Buffer() };
		int widths[] = { left->Width(), right->Width(), top->Width(), bot->Width(), front->Width(), back->Width() };
		int heights[] = { left->Height(), right->Height(), top->Height(), bot->Height(), front->Height(), back->Height() };
		SemanticFormat formats[] = { right->Format(), left->Format(), top->Format(), bot->Format(), back->Format(), front->Format() };
		texture = gl->CreateTextureCube(buffers,widths,heights,formats);

		pass = MakePass();
		pass->SetProgram(pipeline);	

		mesh = LoadMesh(gl,"sphere.obj");
	}
	void render()
	{
		gl->Reset();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		pass->AttachUniform("WVP",MakeUniform(DF_FLOAT4X4,Transpose(vp*w*Scale(Vector3(10000,10000,10000))*Rotate(Vector3(0,1,0),PI))));
		pass->Bind(gl);
		gl->BindTexture("TEXTURE",texture);
		mesh->Bind(gl);
		gl->Draw();
		gl->Reset();
		glDepthFunc(GL_LESS);
		glDisable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);
	}
	void SetVP(Matrix4 vp)
	{
		this->vp = vp;
	}
	void SetLocation(Vector3 location)
	{
		this->w = Translate(location);
	}
private:
	GLPtr gl;
	PassPtr pass;
	MeshPtr mesh;
	TextureID texture;
	Matrix4 w;
	Matrix4 vp;
};
DECLARE_POINTER_OF(SkyBox);
DEF_MAKEFUN_OF(SkyBox);


#endif