#include "Vector3.h"
#include <assert.h>

//construction and destruction
Vector3::Vector3():X(vec[0]),Y(vec[1]),Z(vec[2])
{
}
Vector3::Vector3(float* a):X(vec[0]),Y(vec[1]),Z(vec[2])
{
	vec=Vector<float,3>(a);
}
Vector3::Vector3(const Vector3& v):X(vec[0]),Y(vec[1]),Z(vec[2])
{
	vec=v.vec;
}
Vector3::Vector3(float x, float y, float z):X(vec[0]),Y(vec[1]),Z(vec[2])
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

//assignment
Vector3& Vector3::operator=(const Vector3& v)
{
	vec=v.vec;
	return *this;
}

//access operation
float Vector3::operator[](int i) const
{
	assert(i>=0);
	assert(i<3);
	return vec[i];
}
float& Vector3::operator[](int i)
{
	assert(i>=0);
	assert(i<3);
	return vec[i];
}
float Vector3::operator()(int i) const 
{
	assert(i>0);
	assert(i<=3);
	return vec[i-1];
}
float& Vector3::operator()(int i)
{
	assert(i>0);
	assert(i<=3);
	return vec[i-1];
}

//comparison operation
bool operator==(const Vector3& a,const Vector3& b)
{
	return a.vec==b.vec;
}
bool operator!=(const Vector3& a,const Vector3& b)
{
	return a.vec!=b.vec;
}

//arithmatic operation
Vector3 operator+(const Vector3& a,const Vector3& b) 
{
	Vector3 r;
	r.vec = a.vec+b.vec;
	return r;
}
Vector3 operator-(const Vector3& a,const Vector3& b)
{
	Vector3 r;
	r.vec=a.vec-b.vec;
	return r;
}
Vector3 Vector3::operator-() const
{
	Vector3 r;
	r.vec=-vec;
	return r;
}
Vector3 operator*(const Vector3& v,float k)
{
	Vector3 r;
	r.vec=v.vec*k;
	return r;
}
Vector3 operator/(const Vector3& v,float k)
{
	Vector3 r;
	r.vec=v.vec/k;
	return r;
}
Vector3& Vector3::operator+=(const Vector3& v)
{
	vec+=v.vec;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	vec-=v.vec;
	return *this;
}
Vector3& Vector3::operator*=(float k)
{
	vec*=k;
	return *this;
}
Vector3& Vector3::operator/=(float k)
{
	vec/=k;
	return *this;
}



Vector3 operator*(float k, const Vector3& v)
{
	return v*k;
}
float Dot(const Vector3& a, const Vector3& b)
{
	return Dot(a.vec,b.vec);
}
Vector3 CrossProduct(const Vector3& a, const Vector3& b)
{
	return Vector3( a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0] );
}
float Mag(const Vector3& v)
{
	return Mag(v.vec);
}
Vector3 Normalize(const Vector3& v)
{
	return v/Mag(v);
}