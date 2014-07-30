#ifndef TEXTUREAPP_H
#define TEXTUREAPP_H

#include "App.h"
#include "GL.h"
#include "Mathematics.h"
#include "Canvas.h"
#include "TextureFactory.h"

class TextureApp: public App
{
public:
	void Initialize()
	{
		gl = MakeGL();
		w = glutGet(GLUT_WINDOW_WIDTH);
		h = glutGet(GLUT_WINDOW_HEIGHT);
		glViewport(0,0,w,h);

		can_tex = gl->CreateTexture2D((void*)NULL,w,h,RGBA_FLOAT32);
		can = MakeCanvas();
		can->Init(gl,w,h,gl->CreateFrameBuffer(),can_tex);
		can->Clear();

		ImagePtr pic = LoadImage("guard1_body.png");
		TexturePtr pictx = MakeTexture(gl,pic->Buffer(),pic->Width(),pic->Height(),pic->Format());
		can->DrawTexture(pictx->TexID(),0,w,0,h);
		can->DrawTexture(pictx->TexID(),0,0.5*w,0,0.5*h);

		can->RenderTo(0,0);
	}
	void Display()
	{
		glClearColor(0, 0, 0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		can->DrawTexture(can_tex,(w-h)/2,(w-h)/2+320,0,h);
		glutSwapBuffers();
	}
private:
	GLPtr	gl;
	CanvasPtr can;
	TextureID can_tex;
	float w;
	float h;
};

#endif