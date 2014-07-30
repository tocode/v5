#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Mathematics.h"
#include "GL.h"

class VertexBuffer
{
public:
	VertexBuffer(GLPtr gl,void* buffer,int size)
	{
		this->gl = gl;
		vb = gl->CreateVertexBuffer(buffer,size);
	}
	VertexBufferID GetID()
	{
		return vb;
	}
	~VertexBuffer()
	{
		gl->DeleteVertexBuffer(vb);
	}
private:
	GLPtr gl;
	VertexBufferID vb;
};
DECLARE_POINTER_OF(VertexBuffer);

static VertexBufferPtr MakeVertexBuffer(GLPtr gl,void* buffer,int size)
{
	return VertexBufferPtr(new VertexBuffer(gl,buffer,size));
}
#endif 