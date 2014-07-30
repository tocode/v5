#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>

class Quaternion
{
public:
	float w;
	float x;
	float y;
	float z;
	Quaternion()
	{
		this->w = 1;
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Quaternion(float w,float x,float y,float z)
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Quaternion operator-()
	{
		return Quaternion(-w,-x,-y,-z);
	}
};

static Quaternion Slerp(Quaternion q1, Quaternion q2, float factor)
{
	assert(factor>=0);	
	assert(factor<=1);

	float cosine = q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z;
	if (cosine>1) cosine=1;
	if (cosine<0)
		Slerp(q1,-q2,factor);
	float angle = acos(cosine);	
	float A,B;
	
	if (angle<0.0001)
	{
		A = 1-factor;
		B = factor;
	}
	else
	{
		A = (float)(sin((1.0f-factor)*angle) / sin(angle));
		B = (float)(sin(factor*angle) / sin(angle));
	}

	Quaternion q(1,0,0,0);

	q.w = A*q1.w + B*q2.w;
	q.x = A*q1.x + B*q2.x;
	q.y = A*q1.y + B*q2.y;
	q.z = A*q1.z + B*q2.z;

	return q;
}

static Matrix4 GenRotationMatrix(Quaternion q)
{
	float w = q.w;
	float x = q.x;
	float y = q.y;
	float z = q.z;
	/*return Matrix4
		(
			1-2*y*y,		2*x*y+2*w*z,		2*x*z-2*w*y,		0,
			2*x*y-2*w*z,	1-2*x*x-2*z*z,		2*y*z+2*w*x,		0,
			2*x*z+2*w*y,	2*y*z-2*w*x,		1-2*x*x-2*y*y,		0,
			0,				0,					0,					1
		);*/
	return Matrix4
	(
		1-2*(y*y+z*z),		2*(x*y-z*w),		2*(x*z+y*w),		0,
		2*(x*y+z*w),		1-2*(x*x+z*z),		2*(y*z-x*w),		0,
		2*(x*z-y*w),		2*(y*z+x*w),		1-2*(x*x+y*y),		0,
		0,					0,					0,					1
	);
	/*
	resMatrix.a1 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (y * y + z * z);
	resMatrix.a2 = static_cast<TReal>(2.0) * (x * y - z * w);
	resMatrix.a3 = static_cast<TReal>(2.0) * (x * z + y * w);
	resMatrix.b1 = static_cast<TReal>(2.0) * (x * y + z * w);
	resMatrix.b2 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + z * z);
	resMatrix.b3 = static_cast<TReal>(2.0) * (y * z - x * w);
	resMatrix.c1 = static_cast<TReal>(2.0) * (x * z - y * w);
	resMatrix.c2 = static_cast<TReal>(2.0) * (y * z + x * w);
	resMatrix.c3 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + y * y);
	*/
}









#endif