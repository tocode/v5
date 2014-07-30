#ifndef FONT_H
#define FONT_H

#include <assert.h>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include "Texture.h"
#include "Image.h"

class Font
{
public:
	Font(std::string filename="STHeiti-Medium.ttc")
	{
		Load(filename);
	}
	bool Load(std::string filename)//"simhei.ttf")
	{
		FTlib = NULL;
		FTface = NULL;
		FT_Error error = 0 ;
		//  Init FreeType Lib to manage memory 
		error  =  FT_Init_FreeType( & FTlib);
		if (error)
		{
			FTlib = NULL;
			printf( " There is some error when Init Library " );
			return -1;
		} 
		//  create font face from font file 
		error  =  FT_New_Face(FTlib, filename.c_str(), 0, &FTface);
		if (error) return -1;

		return true;
	}
	ImagePtr MakeCharacterImage(unsigned long c,int width,int height,float r,float g,float b,float a)
	{
		FT_Set_Pixel_Sizes(FTface,width?width:height,height);
		FT_Load_Glyph(FTface, FT_Get_Char_Index(FTface, c), FT_LOAD_DEFAULT);
		FT_Glyph glyph;
		FT_Error error = FT_Get_Glyph(FTface -> glyph, &glyph);
		if (error) exit(0);
		
		//  convert glyph to bitmap with 256 gray 
		FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal,  0 ,  1 );

		//printf("%d\n",glyph->advance.x>>16);
		if (width==0) width = glyph->advance.x>>16;

		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
		FT_Bitmap &bitmap = bitmap_glyph->bitmap;

		int ascender = FTface->size->metrics.ascender>>6;
		int left_space = bitmap_glyph->left;
		int top_space = ascender - bitmap_glyph->top;
		
		if (0)
		for (int i=1; i<=height; i++)
		{
			for (int j=1; j<=width; j++)
				if ( j<=left_space || j>left_space+bitmap.width || i<=top_space || i>top_space+bitmap.rows )
					printf("-");
				else
					printf("%s" , bitmap.buffer[(i-1-top_space)*bitmap.width + (j-1-left_space)] ? "*" : "." );//  if it has gray>0 we set show it as 1, o otherwise 
			printf( "\n" );
		} 
		
		ImagePtr image = MakeImage(NULL,width,height,RGBA_UINT8);
		for (int i=1; i<=height; i++)
			for (int j=1; j<=width; j++)
				if (! ( j<=left_space || j>left_space+bitmap.width || i<=top_space || i>top_space+bitmap.rows ))
				{
					char gray = bitmap.buffer[(i-1-top_space)*bitmap.width + (j-1-left_space)];
					image->Pixel(i,j).r = gray*r;
					image->Pixel(i,j).g = gray*g;
					image->Pixel(i,j).b = gray*b;
					image->Pixel(i,j).a = gray*a;
				}
		image->Flip();
		return image;
	}
	ImagePtr MakeTextImage(std::wstring str,int height,float r,float g,float b,float a)
	{
		int widths = 0;
		vector<ImagePtr> words;
		for (int i=0; i<str.size(); i++)
		{
			ImagePtr word = MakeCharacterImage(str[i],0,height,r,g,b,a);
			words.push_back(word);
			widths += word->Width();
		}
		ImagePtr text_image = MakeImage(NULL,widths,height,RGBA_UINT8);
		int p=0;
		for (int k=0; k<words.size(); k++)
		{
			for (int j=1; j<=words[k]->Width(); j++)
				for (int i=1; i<=words[k]->Height(); i++)
					text_image->Pixel(i,p+j) = words[k]->Pixel(i,j);
			p+=words[k]->Width();
		}	
		return text_image;
	}
	void Cleanup()
	{
		if (FTlib)
		{
			FT_Done_FreeType(FTlib);
			FTlib  =  NULL;
		}
	}
	~Font()
	{
		Cleanup();
	}
	FT_Library		FTlib;
	FT_Face			FTface;
};
DECLARE_POINTER_OF(Font);
FontPtr MakeFont(std::string filename="STHeiti-Medium.ttc")
{
	return FontPtr(new Font(filename));
}

#endif