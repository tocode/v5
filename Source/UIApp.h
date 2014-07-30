#ifndef UIAPP_H
#define UIAPP_H

#include "App.h"
#include "GL.h"
#include "Mathematics.h"
#include "Canvas.h"
#include "Font.h"
#include "TextureFactory.h"
#include "Picture.h"
#include "Label.h"
#include "UIRoot.h"
#include "VLayout.h"
#include "HLayout.h"
#include "Button.h"
#include "HList.h"

void touch_down()
{
	printf("touch_down()\n");
}
void touch_up()
{
	printf("touch_up()\n");
}

class UIApp: public App
{
public:
	void Initialize()
	{
		gl = MakeGL();
		w = glutGet(GLUT_WINDOW_WIDTH);
		h = glutGet(GLUT_WINDOW_HEIGHT);
		glEnable(GL_SCISSOR_TEST);
		glViewport(0,0,w,h);

		cantex = gl->CreateTexture2D((void*)NULL,w,h,RGBA_FLOAT32);

		canvas = MakeCanvas();
		canvas->Init(gl,w,h,0);
		canvas->Clear();

		picture = MakePicture(LoadTexture(gl,"lena.jpg"));
		picture->width=100;
		picture->height=100;

		word = MakeLabel(L"中华民国");

		button = MakeButton(100,100);
		button->text = L"butt";
		button->TouchDown = touch_down;
		button->TouchUp = touch_up;

		hlist = HListPtr(new HList(200,100));
		hlist->Attach(picture);
		hlist->Attach(word);
		hlist->Attach(button);
	}
	void Display()
	{
		canvas->Clear(0,0,0,0);
		hlist->Render(canvas);
	}
	void Touch(UITouch* touch)
	{
		hlist->Touch(touch);
	}
private:
	GLPtr					gl;
	CanvasPtr				canvas;
	float					w;
	float					h;
	TextureID				cantex;

	UIContainerPtr			container;
	PicturePtr				picture;
	LabelPtr				word;
	ButtonPtr				button;
	HListPtr				hlist;
};

#endif