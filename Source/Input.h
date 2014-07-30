#ifndef INPUT_H
#define INPUT_H

#include "Mathematics.h"
#include "GL.h"
#include "VertexBuffer.h"

class Input
{
public:
	Input(VertexBufferPtr vertexbuffer,int offset, int stride, DataFormat format)
	{
		this->vertexbuffer = vertexbuffer;
		this->offset = offset;
		this->stride = stride;
		this->format = format;
	}
	void Bind(GLPtr gl,string semantic)
	{
		gl->BindInput( semantic, vertexbuffer->GetID(), offset, stride, format);
	}
private:
	VertexBufferPtr vertexbuffer;
	int offset;
	int stride;
	DataFormat format;
};
DECLARE_POINTER_OF(Input);

static InputPtr MakeInput(VertexBufferPtr vertexbuffer,int offset, int stride, DataFormat format)
{
	return InputPtr(new Input(vertexbuffer,offset,stride,format));
}
#endif 