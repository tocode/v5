#include "Vector4.h"

Vector4::Vector4():X(vec[0]),Y(vec[1]),Z(vec[2]),W(vec[3])
{
}
Vector4::Vector4(float* a):X(vec[0]),Y(vec[1]),Z(vec[2]),W(vec[3])
{
	vec=Vector<float,4>(a);
}
Vector4::Vector4(const Vector4& v):X(vec[0]),Y(vec[1]),Z(vec[2]),W(vec[3])
{
	vec=v.vec;
}
Vector4::Vector4(float x, float y, float z, float w):X(vec[0]),Y(vec[1]),Z(vec[2]),W(vec[3])
{
	vec[0]=x;
	vec[1]=y;
	vec[2]=z;
	vec[3]=w;
}
Vector4::Vector4(const Vector3& v3, const float w):X(vec[0]),Y(vec[1]),Z(vec[2]),W(vec[3])
{
	X = v3.X;
	Y = v3.Y;
	Z = v3.Z;
	W = w;
}
Vector4& Vector4::operator=(const Vector4& v)
{
	vec=v.vec;
	return *this;
}
float  Vector4::operator[](int i) const
{
	assert(i>=0);
	assert(i<4);
	return vec[i];
}
float& Vector4::operator[](int i)
{
	assert(i>=0);
	assert(i<4);
	return vec[i];
}
float  Vector4::operator()(int i) const
{
	assert(i>0);
	assert(i<=4);
	return vec[i-1];
}
float& Vector4::operator()(int i)
{
	assert(i>0);
	assert(i<=4);
	return vec[i-1];
}
Vector3 Vector4::XYZ() const
{
	return Vector3(vec(1),vec(2),vec(3));
}
bool operator==(const Vector4& a,const Vector4& b) 
{
	return a.vec==b.vec;
}
bool operator!=(const Vector4& a,const Vector4& b) 
{
	return a.vec!=b.vec;
}
Vector4 operator+(const Vector4& a,const Vector4& b)
{
	Vector4 r;
	r.vec=a.vec+b.vec;
	return r;
}
Vector4 operator-(const Vector4& a,const Vector4& b)
{
	Vector4 r;
	r.vec=a.vec-b.vec;
	return r;
}
Vector4 Vector4::operator-() const
{
	Vector4 r;
	r.vec=-vec;
	return r;
}
Vector4 operator*(const Vector4& v,float k)
{
	Vector4 r;
	r.vec=v.vec*k;
	return r;
}
Vector4 operator/(const Vector4& v,float k)
{
	Vector4 r;
	r.vec=v.vec/k;
	return r;
}
Vector4& Vector4::operator+=(const Vector4& v)
{
	vec+=v.vec;
	return *this;
}
Vector4& Vector4::operator-=(const Vector4& v)
{
	vec-=v.vec;
	return *this;
}
Vector4& Vector4::operator*=(float k)
{
	vec*=k;
	return *this;
}
Vector4& Vector4::operator/=(float k)
{
	vec/=k;
	return *this;
}



// k*V
Vector4 operator*(float k, const Vector4& v)
{
	return v*k;
}
// dot - A.B
float Dot(const Vector4& a, const Vector4& b)
{
	return Dot(a.vec,b.vec);
}
// mag
float Mag(const Vector4& v)
{
	return Mag(v.vec);
}
// normalize
Vector4 Normalize(const Vector4& v)
{
	return v/Mag(v);
}