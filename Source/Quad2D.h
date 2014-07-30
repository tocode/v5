#ifndef QUAD2D_H
#define QUAD2D_H

#include "Mesh.h"

class Quad2D
{
public:
	Quad2D(float xmin,float xmax,float ymin,float ymax,float depth,float umin,float umax,float vmin,float vmax)
	{
		mesh = MakeMesh();
		float positions_[] =
		{
			xmin,ymin,depth,
			xmin,ymax,depth,
			xmax,ymax,depth,
			xmax,ymin,depth
		};
		float texcoords_[] =
		{
			umin,vmin,
			umin,vmax,
			umax,vmax,
			umax,vmin
		};
		unsigned int indices_[] =
		{
			0,1,2,
			0,2,3
		};
		memcpy(positions,positions_,sizeof(positions));
		memcpy(texcoords,texcoords_,sizeof(texcoords));
		memcpy(indices,indices_,sizeof(indices));
	}
	void Bind(GLPtr gl)
	{
		pos = MakeVertexBuffer(gl,positions,sizeof(positions));
		txcood = MakeVertexBuffer(gl,texcoords,sizeof(texcoords));
		idx = MakeIndexBuffer(gl,indices,sizeof(indices));
		mesh->AttachInput("POSITION",MakeInput(pos,0,12,DF_FLOAT3));
		mesh->AttachInput("TEXCOOD",MakeInput(txcood,0,8,DF_FLOAT2));
		mesh->SetIndex(MakeIndex(idx,DF_UINT,6));
		mesh->SetPrimitiveTopology(PRIMITIVE_TRIANGLES);
		mesh->Bind(gl);
	}
	~Quad2D()
	{
#ifndef EnableSmartPointer
		delete mesh;
		delete pos;
		delete txcood;
		delete idx;
#endif
	}
private:
	MeshPtr				mesh;
	float				positions[12];
	float				texcoords[8];
	unsigned int		indices[6];
	VertexBufferPtr		pos;
	VertexBufferPtr		txcood;
	IndexBufferPtr		idx;
};
DECLARE_POINTER_OF(Quad2D);

#endif