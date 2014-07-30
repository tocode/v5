#ifndef CANVAS_H
#define CANVAS_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "GL.h"
#include <vector>
#include "Quad2D.h"

using namespace std;

class Canvas
{
public:
	void				Init(GLPtr pgl,int width,int height,TextureID tx=0);
	void				RenderTo(TextureID tx);
	TextureID			CanvasTexture();
	void				Clear(float r=0,float g=0,float b=0,float a=0);
	void				DrawTexture(TextureID tx,int x1,int x2,int y1,int y2,float depth=0.5,float u1=0,float u2=1,float v1=0,float v2=1);
	float				Width();
	float				Height();
	GLPtr				GL(){ return canvas_gl; }
	void				Scissor(float x,float y,float w,float h);
private:
	void				Begin();
	void				End();
	void				DrawTextureRaw(TextureID tx,float x1,float x2,float y1,float y2,float depth=0.5,float u1=0,float u2=1,float v1=0,float v2=1);
private:
	GLPtr					canvas_gl;
	float					canvas_width;
	float					canvas_height;
	ShaderID				canvas_vs;
	ShaderID				canvas_fs;
	ProgramID				canvas_pl;
	TextureID				canvas_tx;
};
DECLARE_POINTER_OF(Canvas);
DEF_MAKEFUN_OF(Canvas);

#endif