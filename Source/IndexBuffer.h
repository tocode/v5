#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "Mathematics.h"
#include "GL.h"

class IndexBuffer
{
public:
	IndexBuffer(GLPtr gl,void* buffer,int size)
	{
		this->gl = gl;
		ib = gl->CreateIndexBuffer(buffer,size);
	}
	IndexBufferID GetID()
	{
		return ib;
	}
	~IndexBuffer()
	{
		gl->DeleteIndexBuffer(ib);
	}
private:
	GLPtr gl;
	IndexBufferID ib;
};
DECLARE_POINTER_OF(IndexBuffer);

static IndexBufferPtr MakeIndexBuffer(GLPtr gl,void* buffer,int size)
{
	return IndexBufferPtr(new IndexBuffer(gl,buffer,size));
}
#endif 