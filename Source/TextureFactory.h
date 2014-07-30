#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "FreeImage.h"
#include "GL.h"
#include "Texture.h"
#include "Image.h"

ImagePtr LoadImage(std::string filename)
{
	FreeImage_Initialise();

	FREE_IMAGE_FORMAT filetype = FreeImage_GetFileType(filename.c_str());
	if(filetype == FIF_UNKNOWN) filetype = FreeImage_GetFIFFromFilename(filename.c_str());
	if(filetype == FIF_UNKNOWN)	exit(0);

	FIBITMAP *bitmap=NULL;
	if(FreeImage_FIFSupportsReading(filetype))
		bitmap = FreeImage_Load(filetype, filename.c_str());
	if(!bitmap)	exit(0);

	bitmap=FreeImage_ConvertTo32Bits(bitmap);
	int bpp = FreeImage_GetBPP(bitmap);
	BYTE* buf = FreeImage_GetBits(bitmap);
	int width = FreeImage_GetWidth(bitmap);
	int height = FreeImage_GetHeight(bitmap);
	assert(bpp==32);
	if((buf == 0) || (width == 0) || (height == 0))
		exit(0);
	
	int line = FreeImage_GetLine(bitmap);
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			BYTE t=buf[i*line+j*4];
			buf[i*line+j*4]=buf[i*line+j*4+2];
			buf[i*line+j*4+2]=t;
		}
	return MakeImage(buf,width,height,RGBA_UINT8);
}
TexturePtr MakeTexture(GLPtr gl,ImagePtr image)
{
	return MakeTexture(gl,image->Buffer(),image->Width(),image->Height(),image->Format());
}
TexturePtr LoadTexture(GLPtr gl,std::string filename)
{
	return MakeTexture(gl,LoadImage(filename));
}


#endif