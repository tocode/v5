#ifndef PICTURE_H
#define PICTURE_H

#include "UIComponent.h"
#include "Texture.h"
#include "Canvas.h"
#include "TextureFactory.h"
#include "UIContainer.h"

class Picture: public UIComponent
{
public:
	Picture(TexturePtr texture)
	{
		this->texture = texture;
		this->width = texture->Width();
		this->height = texture->Height();
	}
	void Render(CanvasPtr canvas)
	{
		canvas->DrawTexture(texture->TexID(),
			AbsoluteX(),
			AbsoluteX()+width,
			canvas->Height()-AbsoluteY()-height,
			canvas->Height()-AbsoluteY());
	}
private:
	TexturePtr texture;
};

DECLARE_POINTER_OF(Picture);

static PicturePtr MakePicture(TexturePtr tex)
{
	return PicturePtr(new Picture(tex));
}


#endif