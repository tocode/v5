#ifndef UNIFORM_H
#define UNIFORM_H

#include "Mathematics.h"
#include "GL.h"
#include <vector>

class Uniform
{
public:
	Uniform(DataFormat type,void* buffer,int count)
	{
		this->type = type;
		this->buffer = buffer;
		this->count = count;
	}
	void Bind(GLPtr gl,string semantic)
	{
		gl->BindUniform(semantic,type,buffer,count);
	}
private:
	DataFormat type;
	void* buffer;
	int count;
};
DECLARE_POINTER_OF(Uniform);

static UniformPtr MakeUniform(DataFormat type,void* buffer,int count=1)
{
	return UniformPtr(new Uniform(type,buffer,count));
}
#endif