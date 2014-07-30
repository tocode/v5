#ifndef HLIST_H
#define HLIST_H

#include "UIContainer.h"
#include "GestureRecognizer.h"

using namespace std::placeholders;

class HList: public UIContainer
{
public:
	HList(float w,float h)
	{
		this->width = w;
		this->height = h;
		this->texture = 0;
		this->offset = 0;
	}
	void Render(CanvasPtr can)
	{
		if (!texture)
		{
			texture = MakeTexture(can->GL(),NULL,can->Width(),can->Height(),RGBA_FLOAT32);
			TextureID oldtx = can->CanvasTexture();
			Layout(offset,0);
			can->RenderTo(texture->TexID());
			
			can->Scissor(x,y,width,height);
			can->Clear();
			UIContainer::Render(can);
			can->Scissor(0,0,can->Width(),can->Height());

			can->RenderTo(oldtx);
		}
		
		can->DrawTexture(texture->TexID(),0,can->Width(),0,can->Height());
	}
	void Touch(const UITouch* touch)
	{
		gesture.x = AbsoluteX();
		gesture.y = AbsoluteY();
		gesture.w = width;
		gesture.h = height;
		gesture.TouchMove = bind(&HList::Drag,THIS_OF(HList),_1,_2);
		gesture.Touch(touch);

		UIContainer::Touch(touch);
	}
private:
	void Drag(int dx,int dy)
	{
		offset+=dx;
		texture = NULL;
	}
	void Layout(float left_space,float space)
	{
		float pos=left_space;
		for (int i=0; i<components.size(); i++)
		{
			components[i]->x = pos;
			pos+=components[i]->width;
			pos+=space;
		}
	}
private:
	GestureRecognizer			gesture;
	TexturePtr					texture;
	float						offset;
};

DECLARE_POINTER_OF(HList);


#endif