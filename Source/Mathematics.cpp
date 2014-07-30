#ifndef MATHEMATICS_INL
#define MATHEMATICS_INL

#include "Mathematics.h"

Vector3 operator*(const Matrix3& m, const Vector3& v)
{
	return Vector3( Dot(m.Row(1),v), Dot(m.Row(2),v), Dot(m.Row(3),v) );
}
Vector4 operator*(const Matrix4& m, const Vector4& v)
{
	return Vector4( Dot(m.Row(1),v), Dot(m.Row(2),v), Dot(m.Row(3),v), Dot(m.Row(3),v) );
}

Matrix4 Identity()
{
	return Matrix4
		(
		1,		0,		0,		0,
		0,		1,		0,		0,
		0,		0,		1,		0,
		0,		0,		0,		1
		);
}

Matrix4 Translate(const Vector3& v)
{
	return Transpose(Matrix4
		(		
		1,		0,		0,		0,
		0,		1,		0,		0,
		0,		0,		1,		0,
		v[0],	v[1],	v[2],	1
		));
}
Matrix4 Scale(const Vector3& v)
{
	return Matrix4
	(
		v.X,	0,		0,		0,
		0,		v.Y,	0,		0,
		0,		0,		v.Z,	0,
		0,		0,		0,		1
	);
}
Matrix4 Rotate( const Vector3& v, float angle )
{
	float sin_a = sin(angle);
	float cos_a = cos(angle);
	float term = 1 - cos(angle);
	float x = v[0];
	float y = v[1];
	float z = v[2];

	return Transpose(Matrix4
		(	
		x*x*term + cos_a,		x*y*term + z*sin_a,		x*z*term - y*sin_a,		0,
		x*y*term - z*sin_a,		y*y*term + cos_a,		y*z*term + x*sin_a,		0,
		x*z*term + y*sin_a,		y*z*term - x*sin_a,		z*z*term + cos_a,		0,
		0,						0,						0,						1
		));
}
Matrix4 Frustum(float left, float right, float bottom, float top, float near, float far)
{
	float       deltaX = right - left;
	float       deltaY = top - bottom;
	float       deltaZ = far - near;
	assert(	!( (near<=0.0f)||(far<=0.0f)||(deltaX<=0.0f)||(deltaY<=0.0f)||(deltaZ<=0.0f) ) );

	return Transpose(Matrix4
		(	
		2 * near / deltaX,				0,								0,									0,
		0,								2 * near / deltaY,				0,									0,
		(right + left) / deltaX,		(top + bottom) / deltaY,		-(near + far) / deltaZ,				-1,
		0,								0,								-2 * near * far / deltaZ,			0
		));
}
Matrix4 Perspective(float fovy, float aspect, float nearZ, float farZ)
{
	float frustumH = tanf( fovy / 360.0f * PI ) * nearZ;
	float frustumW = frustumH * aspect;
	return Frustum(-frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
}
Matrix4 Ortho(float left, float right, float bottom, float top, float nearVal, float farVal)
{
	float w = right - left;
	float h = top - bottom;
	float n_f = nearVal - farVal;
	return
		Matrix4
		(
		1,			0,			0,			0,
		0,			1,			0,			0,
		0,			0,			0,			0,
		0,			0,			0,			1
		)
		*
		Matrix4
		(	
		2/w,		0,			0,			-(right+left)/w,
		0,			2/h,		0,			-(top+bottom)/h,
		0,			0,			2/n_f,		(nearVal+farVal)/n_f,
		0,			0,			0,			1
		);
}

Matrix4 LookAt(const Vector3 eye,const Vector3 target,Vector3 up)
{
	Vector3 forward = Normalize(target - eye);
	Vector3 right = Normalize(CrossProduct(forward,up));
	up = CrossProduct(right,forward);

	return Inverse(Matrix4
		(
			right[0],	up[0],	-forward[0],	0,
			right[1],	up[1],	-forward[1],	0,
			right[2],	up[2],	-forward[2],	0,
			0,			0,		0,				1
		))
		*
		Matrix4
		(
			1,		0,		0,		-eye[0],
			0,		1,		0,		-eye[1],
			0,		0,		1,		-eye[2],
			0,		0,		0,		1
		);
}



#endif