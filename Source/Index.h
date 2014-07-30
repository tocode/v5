#ifndef INDEX_H
#define INDEX_H

#include "Mathematics.h"
#include "GL.h"
#include "IndexBuffer.h"

class Index
{
public:
	Index(IndexBufferPtr ib,DataFormat format, int count)
	{
		this->ib = ib;
		this->format = format;
		this->count = count;
	}
	void Bind(GLPtr gl)
	{
		gl->BindIndex(ib->GetID(),format,count);
	}
private:
	IndexBufferPtr ib;
	DataFormat format;
	int count;
};
DECLARE_POINTER_OF(Index);


static IndexPtr MakeIndex(IndexBufferPtr ib,DataFormat format, int count)
{
	return IndexPtr(new Index(ib,format,count));
}


#endif