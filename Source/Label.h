#ifndef LABEL_H
#define LABEL_H

#include "UIComponent.h"
#include "Texture.h"
#include "Canvas.h"
#include "TextureFactory.h"
#include "Font.h"

enum Alignment
{
	ALIGNMENT_LEFT,
	ALIGNMENT_RIGHT,
	ALIGNMENT_CENTER,
};

class Label: public UIComponent
{
public:
	Label(std::wstring text,int size=40,FontPtr font=NULL)
	{
		this->text = text;
		this->size = size;
		this->color = Color();
		this->alignment = ALIGNMENT_LEFT;
		this->texture = NULL;
		this->font = font ? font : MakeFont();
		ImagePtr image = this->font->MakeTextImage(text,size,color.r,color.g,color.b,color.a);
		this->width = image->Width();
		this->height = image->Height();
	}
	void Render(CanvasPtr canvas)
	{
		if ( !texture )
			texture = MakeTexture(canvas->GL(),font->MakeTextImage(text,size,color.r,color.g,color.b,color.a));
		
		if ( texture->Width() > width )
			alignment = ALIGNMENT_LEFT;
		
		float x1,x2;
		switch( alignment )
		{
			case ALIGNMENT_LEFT:
				x1=AbsoluteX();
				x2=AbsoluteX()+texture->Width();
				break;
			case ALIGNMENT_RIGHT:
				x1=AbsoluteX() + width - texture->Width();
				x2=AbsoluteX()+width;
				break;
			case ALIGNMENT_CENTER:
				x1=AbsoluteX() + ( width - texture->Width() )/2;
				x2=x1+texture->Width();
				break;
			default:
				assert(0);
		}

		canvas->DrawTexture(texture->TexID(),
			x1,x2,
			canvas->Height()-AbsoluteY()-texture->Height(),
			canvas->Height()-AbsoluteY());
	}
	void SetText(std::wstring text)
	{
		this->text = text;
		texture = NULL;
	}
	void SetSize(int size)
	{
		this->size = size;
		texture = NULL;
	}
	void SetColor(Color color)
	{
		this->color = color;
		texture = NULL;
	}
	void SetAlignment(Alignment alignment)
	{
		this->alignment = alignment;
	}
public:
	std::wstring	text;
	int				size;
	Color			color;
	Alignment		alignment;
private:
	TexturePtr		texture;
	FontPtr			font;

};

DECLARE_POINTER_OF(Label);

LabelPtr MakeLabel(std::wstring text,int size=40,FontPtr font=0)
{
	return LabelPtr(new Label(text,size,font));
}


#endif