#ifndef TEXTURE_H
#define TEXTURE_H

#include "Mathematics.h"
#include "GL.h"
#include <vector>

class Texture
{
public:
	Texture(GLPtr gl,void* buffer,int width,int height,SemanticFormat format)
	{
		this->tx = gl->CreateTexture2D(buffer,width,height,format);
		this->gl = gl;
		this->width = width;
		this->height = height;
		this->format = format;
	}
	~Texture()
	{
		if (gl);
			gl->DeleteTexture(this->tx);
	}
	void Bind(string semantic)
	{
		gl->BindTexture(semantic,tx);
	}
	TextureID TexID()
	{
		return tx;
	}
	int Width()
	{
		return width;
	}
	int Height()
	{
		return height;
	}
	SemanticFormat Format()
	{
		return format;
	}
private:
	GLPtr			gl;
	TextureID		tx;
	int				width;
	int				height;
	SemanticFormat	format;
};

DECLARE_POINTER_OF(Texture);

static TexturePtr MakeTexture(GLPtr gl,void* buffer,int width,int height,SemanticFormat format)
{
	return TexturePtr(new Texture(gl,buffer,width,height,format));
}
#endif