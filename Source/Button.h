#ifndef BUTTON_H
#define BUTTON_H

#include "UIComponent.h"
#include "Picture.h"
#include "Label.h"
#include "GestureRecognizer.h"

class Button: public UIComponent
{
public:
	Button(float w,float h)
	{
		this->width = w;
		this->height = h;
		this->picture = NULL;
		this->label = NULL;
		this->texture = NULL;
		this->text = L"";
	}
	void Render(CanvasPtr can)
	{
		if (texture)
		{
			if (!picture)
				picture = MakePicture(texture);
			picture->Render(can);
		}
		if (text!=L"")
		{
			if (!label)
				label = MakeLabel(text);
			
			label->x = AbsoluteX();
			label->y = AbsoluteY();
			label->Render(can);
		}
	}
	void Touch(const UITouch* touch)
	{
		gesture.x = AbsoluteX();
		gesture.y = AbsoluteY();
		gesture.w = width;
		gesture.h = height;
		gesture.TouchDown = TouchDown;
		gesture.TouchUp = TouchUp;
		gesture.Touch(touch);
	}
public:
	TexturePtr					texture;
	std::wstring				text;
	std::function<void ()>		TouchDown;
	std::function<void ()>		TouchUp;
private:
	PicturePtr					picture;
	LabelPtr					label;
	GestureRecognizer			gesture;
};

DECLARE_POINTER_OF(Button);

ButtonPtr MakeButton(float w,float h)
{
	return ButtonPtr(new Button(w,h));
}


#endif