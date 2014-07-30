#include "Canvas.h"
#include "Mathematics.h"
#include "Quad2D.h"

void Canvas::Init(GLPtr glrenderer,int width,int height,TextureID tx)
{
	canvas_gl = glrenderer;
	canvas_width = width;
	canvas_height = height;

	string canvas_vs_src =  
		"attribute vec4 a_position;									\n"
		"attribute vec2 a_texcood;									\n"
		"uniform mat4 u_wvp;										\n"
		"varying vec2 v_texcood;									\n"
		"void main()												\n"
		"{															\n"
		"   gl_Position = u_wvp * a_position;						\n"
		"	v_texcood = a_texcood;									\n"
		"}															\n";
	string canvas_fs_src =  
		"varying vec2 v_texcood;									\n"
		"uniform sampler2D s_texture;								\n"
		"void main()												\n"
		"{															\n"
		"	gl_FragColor = texture2D(s_texture,v_texcood);			\n"
		"}															\n";
	canvas_vs = canvas_gl->CreateShader(VertexShader,canvas_vs_src);
	canvas_fs = canvas_gl->CreateShader(FragmentShader,canvas_fs_src);
	canvas_pl = canvas_gl->CreateProgram(canvas_vs,canvas_fs);
	canvas_gl->DeclareAttribute( "POSITION", "a_position",  canvas_pl);
	canvas_gl->DeclareAttribute( "TEXCOOD",  "a_texcood",   canvas_pl);
	canvas_gl->DeclareUniform  ( "WVP",      "u_wvp",		canvas_pl);
	canvas_gl->DeclareTexture  ( "TEXTURE",  "s_texture",   canvas_pl);
	canvas_gl->BindProgram(canvas_pl);

	RenderTo(tx);
	
	Matrix4 model = Identity();
	Matrix4 view = Identity();
	Matrix4 projection = Ortho(0,1,0,1,1,0);
	static Matrix4 wvp = Transpose(projection*view*model);
	canvas_gl->BindUniform("WVP",DF_FLOAT4X4,wvp);
}
void Canvas::RenderTo(TextureID tx)
{
	canvas_tx = tx;
	canvas_gl->BindColorBuffer(0,canvas_tx);
}
void Canvas::Clear(float r,float g,float b,float a)
{
	canvas_gl->ClearColorBuffer(r,g,b,a);
}
void Canvas::Begin()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
void Canvas::End()
{
	glDisable(GL_BLEND);
}
void Canvas::DrawTextureRaw(TextureID tx,float x1,float x2,float y1,float y2,float depth,float u1,float u2,float v1,float v2)
{
	Begin();
	Quad2D quad = Quad2D(x1,x2,y1,y2,depth,u1,u2,v1,v2);
	quad.Bind(canvas_gl);
	canvas_gl->BindTexture("TEXTURE",tx);
	canvas_gl->Draw();
	End();
}
void Canvas::DrawTexture(TextureID tx,int x1,int x2,int y1,int y2,float depth,float u1,float u2,float v1,float v2)
{
	DrawTextureRaw(tx,x1/canvas_width,x2/canvas_width,y1/canvas_height,y2/canvas_height,depth,u1,u2,v1,v2);
}
TextureID Canvas::CanvasTexture()
{
	return canvas_tx;
}
float Canvas::Width()
{
	return canvas_width;
}
float Canvas::Height()
{
	return canvas_height;
}
void Canvas::Scissor(float x,float y,float w,float h)
{
	canvas_gl->Scissor(x,canvas_height-y-h,w,h);
}