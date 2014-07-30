#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "Mathematics.h"

Vector3::Vector3(float f3[])
{
	f[0]=f3[0];
	f[1]=f3[1];
	f[2]=f3[2];
}
Vector3::Vector3(float x,float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
float Vector3::operator[](int i) const
{
	return f[i];
}
Vector3 operator+(Vector3 a,Vector3 b)
{
	return Vector3( a.x+b.x, a.y+b.y, a.z+b.z );
}
Vector3 operator-(Vector3 a,Vector3 b)
{
	return Vector3( a.x-b.x, a.y-b.y, a.z-b.z );
}
Vector3 operator*(Vector3 a,float k)
{
	return Vector3( a.x * k, a.y * k, a.z * k);
}
Vector3 operator*(float k,Vector3 a)
{
	return a*k;
}
Vector3 operator/(Vector3 a,float k)
{
	return a*(1/k);
}
bool operator==(Vector3 a,Vector3 b)
{
	float dx = abs(a.x - b.x);
	float dy = abs(a.y - b.y);
	float dz = abs(a.z - b.z);
	float e = 0.000001;
	return dx + dy + dz < e;
}
bool operator!=(Vector3 a,Vector3 b)
{
	return !(a==b);
}
Vector3& operator+=(Vector3& a,Vector3 b)
{
	a = a + b;
	return a;
}
Vector3& operator-=(Vector3& a,Vector3 b)
{
	a = a - b;
	return a;
}
float   Dot(Vector3 a,Vector3 b)
{
	float sum = 0;
	for (int i=0; i<3; i++)
		sum += a.f[i] * b.f[i];
	return sum;
}
float   Norm(Vector3 a)
{
	return sqrt(Dot(a,a));
}
Vector3 Normalize(Vector3 a)
{
	return a/Norm(a);
}


Vector4::Vector4(float f4[])
{
	f[0] = f4[0];
	f[1] = f4[1];
	f[2] = f4[2];
	f[3] = f4[3];
}
Vector4::Vector4(float x,float y,float z,float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4 operator+(Vector4 a,Vector4 b)
{
	return Vector4( a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w );
}
Vector4 operator-(Vector4 a,Vector4 b)
{
	return Vector4( a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w );
}
Vector4 operator*(Vector4 a,float k)
{
	return Vector4( a.x * k, a.y * k, a.z * k, a.w * k );
}
Vector4 operator*(float k,Vector4 a)
{
	return a*k;
}
Vector4 operator/(Vector4 a,float k)
{
	return a*(1/k);
}
bool operator==(Vector4 a,Vector4 b)
{
	float dx = abs(a.x - b.x);
	float dy = abs(a.y - b.y);
	float dz = abs(a.z - b.z);
	float dw = abs(a.w - b.w);
	float e = 0.000001;
	return dx + dy + dz + dw < e;
}
bool operator!=(Vector4 a,Vector4 b)
{
	return !(a==b);
}
Vector4& operator+=(Vector4& a,Vector4 b)
{
	a = a + b;
	return a;
}
Vector4& operator-=(Vector4& a,Vector4 b)
{
	a = a - b;
	return a;
}
float Dot(Vector4 a,Vector4 b)
{
	float sum = 0;
	for (int i=0; i<4; i++)
		sum += a.f[i] * b.f[i];
	return sum;
}
float Norm(Vector4 a)
{
	return sqrt(Dot(a,a));
}
Vector4 Normalize(Vector4 a)
{
	return a/Norm(a);
}


Matrix3::Matrix3()
{
	*this = Matrix3(0,0,0,0,0,0,0,0,0);
}
Matrix3::Matrix3(float f9[])
{
	*this = Matrix3(f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8]);
}
Matrix3::Matrix3(float m11,float m12,float m13,float m21,float m22,float m23,float m31,float m32,float m33)
{
	this->m11 = m11;	this->m12 = m12;	this->m13 = m13;
	this->m21 = m21;	this->m22 = m22;	this->m23 = m23;
	this->m31 = m31;	this->m32 = m32;	this->m33 = m33;
}
Matrix3 operator+(Matrix3 a,Matrix3 b)
{
	Matrix3 c;
	for (int i=0; i<9; i++)
		c.f[i] = a.f[i] + b.f[i];
	return c;
}
Matrix3 operator-(Matrix3 a,Matrix3 b)
{
	Matrix3 c;
	for (int i=0; i<9; i++)
		c.f[i] = a.f[i] - b.f[i];
	return c;
}
Matrix3 operator*(Matrix3 a,Matrix3 b)
{
	Matrix3 c;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			for (int k=0; k<3; k++)
				c.m[i][j] += a.m[i][k] * b.m[k][j];
	return c;
}
Matrix3 operator*(Matrix3 a,float k)
{
	Matrix3 c;
	for (int i=0; i<9; i++)
		c.f[i] = a.f[i] * k;
	return c;
}
Matrix3 operator*(float k,Matrix3 a)
{
	return a*k;
}
Matrix3 operator/(Matrix3 a,float k)
{
	return a*(1/k);
}
bool operator==(Matrix3 a,Matrix3 b)
{
	float sum = 0;
	for (int i=0; i<9; i++)
		sum += abs(a.f[i] - b.f[i]);
	return sum<0.000001;
}
bool operator!=(Matrix3 a,Matrix3 b)
{
	return !(a==b);
}
Matrix3& operator+=(Matrix3& a,Matrix3 b)
{
	a = a + b;
	return a;
}
Matrix3& operator-=(Matrix3& a,Matrix3 b)
{
	a = a - b;
	return a;
}
Matrix3 Transpose(Matrix3 m)
{
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			if (i<j)
			{
				float t = m.m[i][j];
				m.m[i][j] = m.m[j][i];
				m.m[j][i] = t;
			}
			return m;
}


Matrix4::Matrix4()
{
	*this = Matrix4(0.0f,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
Matrix4::Matrix4(float f[])
{
	*this = Matrix4(f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8],f[9],f[10],f[11],f[12],f[13],f[14],f[15]);	
}
Matrix4::Matrix4(float m11,float m12,float m13,float m14,float m21,float m22,float m23,float m24,float m31,float m32,float m33,float m34,float m41,float m42,float m43,float m44)
{
	this->m11 = m11;	this->m12 = m12;	this->m13 = m13;	this->m14 = m14;
	this->m21 = m21;	this->m22 = m22;	this->m23 = m23;	this->m24 = m24;
	this->m31 = m31;	this->m32 = m32;	this->m33 = m33;	this->m34 = m34;
	this->m41 = m41;	this->m42 = m42;	this->m43 = m43;	this->m44 = m44;
}
Matrix4::operator float*()
{
	return f;
}
Matrix4 operator+(Matrix4 a,Matrix4 b)
{
	Matrix4 c;
	for (int i=0; i<16; i++)
		c.f[i] = a.f[i] + b.f[i];
	return c;
}
Matrix4 operator-(Matrix4 a,Matrix4 b)
{
	Matrix4 c;
	for (int i=0; i<16; i++)
		c.f[i] = a.f[i] - b.f[i];
	return c;
}
Matrix4 operator*(Matrix4 a,Matrix4 b)
{
	Matrix4 c;
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			for (int k=0; k<4; k++)
				c.m[i][j] += a.m[i][k] * b.m[k][j];
	return c;
}
Matrix4 operator*(Matrix4 a,float k)
{
	Matrix4 c;
	for (int i=0; i<16; i++)
		c.f[i] = a.f[i] * k;
	return c;
}
Matrix4 operator*(float k,Matrix4 a)
{
	return a*k;
}
Matrix4 operator/(Matrix4 a,float k)
{
	return a*(1/k);
}
bool operator==(Matrix4 a,Matrix4 b)
{
	float sum = 0;
	for (int i=0; i<16; i++)
		sum += abs(a.f[i] - b.f[i]);
	return sum<0.000001;
}
bool operator!=(Matrix4 a,Matrix4 b)
{
	return !(a==b);
}
Matrix4& operator+=(Matrix4& a,Matrix4 b)
{
	a = a + b;
	return a;
}
Matrix4& operator-=(Matrix4& a,Matrix4 b)
{
	a = a - b;
	return a;
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

Matrix4 Transpose(Matrix4 m)
{
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			if (i<j)
			{
				float t = m.m[i][j];
				m.m[i][j] = m.m[j][i];
				m.m[j][i] = t;
			}
	return m;
}
void Matrix4::print()
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			printf("%f\t",m[i][j]);
		printf("\n");
	}
	printf("\n");
}
Vector3 CrossProduct(Vector3 a,Vector3 b)
{
	return Vector3(a[1]*b[2]-a[2]*b[1],a[3]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]);
}

float Det(Matrix3 m)
{
	return m(0)*(m(4)*m(8))-m(1)*(m(3)*m(8)-m(5)*m(6))+m(2)*(m(3)*m(7)-m(4)*m(6));
}
float Det(Matrix4 m)
{
	return 0;
}
Matrix4 LookAt(const Vector3 eye,const Vector3 target,Vector3 up)
{
	Vector3 forward = Normalize(target - eye);
	Vector3 right = Normalize(CrossProduct(forward,up));
	up = CrossProduct(right,forward);

	return Matrix4
		(
			right[0],right[1],right[2],0,
			up[0],up[1],up[2],0,
			-forward[0],-forward[1],-forward[2],0,
			-eye[0],-eye[1],-eye[2],1
		);
}