#ifndef IMAGE_H
#define IMAGE_H

#include "GL.h"

int SizeOf(SemanticFormat format)
{
	switch(format)
	{
	case RGB_UINT8:
		return 3;
	case RGBA_UINT8:
		return 4;
	case RGB_FLOAT32:
		return 12;
	case RGBA_FLOAT32:
		return 16;
	default:
		assert(0);
	}
}
class Color
{
public:
	char r,g,b,a;
	Color(float r=1,float g=1,float b=1,float a=1)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};
class Image
{
public:
	Image(void* buffer,int width,int height,SemanticFormat format)
	{
		this->width = width;
		this->height = height;
		this->format = format;
		this->buffer = malloc(Size());
		if (buffer)
			memcpy(this->buffer,buffer,Size());
		else
			memset(this->buffer,0,Size());
	}
	Color& Pixel(int i,int j)
	{
		return ((Color*)buffer)[(i-1)*width+(j-1)];
	}
	void Flip()
	{
		for (int i=0; i<height/2; i++)
			for (int j=0; j<width; j++)
			{
				Color c = ((Color*)buffer)[i*width+j];
				((Color*)buffer)[i*width+j] = ((Color*)buffer)[(height-i-1)*width+j];
				((Color*)buffer)[(height-i-1)*width+j] = c;
			}
	}
	int Width() const
	{
		return width;
	}
	int Height() const
	{
		return height;
	}
	void* Buffer()
	{
		return buffer;
	}
	int Size()
	{
		return width*height*SizeOf(format);
	}
	SemanticFormat Format()
	{
		return format;
	}
	~Image()
	{
		if (buffer)
			free(buffer);
	}
private:
	int					width;
	int					height;
	void*				buffer;
	SemanticFormat		format;
};

DECLARE_POINTER_OF(Image);

static ImagePtr MakeImage(void* buffer,int width,int height,SemanticFormat format)
{
	return ImagePtr(new Image(buffer,width,height,format));
}


#endif