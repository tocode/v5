#ifndef CANVASAPP_H
#define CANVASAPP_H

#include "App.h"
#include "GL.h"
#include "Mathematics.h"
#include "Canvas.h"
#include "Font.h"
#include "TextureFactory.h"
#include "Picture.h"

class CanvasApp: public App
{
public:
	void Initialize()
	{
		gl = MakeGL();
		width = glutGet(GLUT_WINDOW_WIDTH);
		height = glutGet(GLUT_WINDOW_HEIGHT);
		glViewport(0,0,width,height);

		Font font;
		cantex = gl->CreateTexture2D((void*)NULL,width,height,RGBA_FLOAT32);
		background = LoadTexture(gl,"lena.jpg");
		word = MakeTexture(gl,font.MakeTextImage(L"中华民国",40,1,0,0,1));
		
		can = MakeCanvas();
		can->Init(gl,width,height,cantex);
		
		can->Clear();
		can->DrawTexture(background->TexID(),0,width,0,height);
		can->DrawTexture(word->TexID(),0,0.5*width,0,height);
		
		can->RenderTo(0);
		can->Clear();
		can->DrawTexture(cantex,0,width,0,height);
		//can->DrawTexture(background->TexID(),0,width,0,height);
	}
	void Display()
	{

	}
private:
	GLPtr				gl;
	CanvasPtr			can;
	float				width;
	float				height;
	TextureID			cantex;
	TexturePtr			background;
	TexturePtr			word;
};

#endif