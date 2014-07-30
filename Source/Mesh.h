#ifndef MESH_H
#define MESH_H

#include "Mathematics.h"
#include "GL.h"
#include "Input.h"
#include "Index.h"

class Mesh
{
public:
	void AttachInput(string semantic,InputPtr input)
	{
		inputs[semantic] = input;
	}
	void SetIndex(IndexPtr index)
	{
		this->index = index;
	}
	void SetPrimitiveTopology(PrimitiveType primitive)
	{
		this->primitive = primitive;
	}
	void Bind(GLPtr gl)
	{
		for (auto it=inputs.begin(); it!=inputs.end(); it++)
		{
			auto semantic = it->first;
			auto input = it->second;
			input->Bind(gl,semantic);
		}
		index->Bind(gl);
		gl->BindPrimitiveTopology(primitive);
	}
private:
	//GLPtr gl;
	map<string,InputPtr> inputs;
	IndexPtr index;
	PrimitiveType primitive;
};
DECLARE_POINTER_OF(Mesh);
DEF_MAKEFUN_OF(Mesh);

#endif