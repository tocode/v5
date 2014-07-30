#include "Vector2.h"
#include <assert.h>

//construction and destruction
Vector2::Vector2():X(vec[0]),Y(vec[1])
{
}
Vector2::Vector2(float* a):X(vec[0]),Y(vec[1])
{
	vec=Vector<float,2>(a);
}
Vector2::Vector2(const Vector2& v):X(vec[0]),Y(vec[1])
{
	vec=v.vec;
}
Vector2::Vector2(float x, float y):X(vec[0]),Y(vec[1])
{
	vec[0] = x;
	vec[1] = y;
}

//assignment
Vector2& Vector2::operator=(const Vector2& v)
{
	vec=v.vec;
	return *this;
}

//access operation
float Vector2::operator[](int i) const
{
	assert(i>=0);
	assert(i<2);
	return vec[i];
}
float& Vector2::operator[](int i)
{
	assert(i>=0);
	assert(i<2);
	return vec[i];
}
float Vector2::operator()(int i) const 
{
	assert(i>0);
	assert(i<=2);
	return vec[i-1];
}
float& Vector2::operator()(int i)
{
	assert(i>0);
	assert(i<=2);
	return vec[i-1];
}

//comparison operation
bool operator==(const Vector2& a,const Vector2& b)
{
	return a.vec==b.vec;
}
bool operator!=(const Vector2& a,const Vector2& b)
{
	return a.vec!=b.vec;
}

//arithmatic operation
Vector2 operator+(const Vector2& a,const Vector2& b) 
{
	Vector2 r;
	r.vec = a.vec+b.vec;
	return r;
}
Vector2 operator-(const Vector2& a,const Vector2& b)
{
	Vector2 r;
	r.vec=a.vec-b.vec;
	return r;
}
Vector2 Vector2::operator-() const
{
	Vector2 r;
	r.vec=-vec;
	return r;
}
Vector2 operator*(const Vector2& v,float k)
{
	Vector2 r;
	r.vec=v.vec*k;
	return r;
}
Vector2 operator/(const Vector2& v,float k)
{
	Vector2 r;
	r.vec=v.vec/k;
	return r;
}
Vector2& Vector2::operator+=(const Vector2& v)
{
	vec+=v.vec;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& v)
{
	vec-=v.vec;
	return *this;
}
Vector2& Vector2::operator*=(float k)
{
	vec*=k;
	return *this;
}
Vector2& Vector2::operator/=(float k)
{
	vec/=k;
	return *this;
}

Vector2 operator*(float k, const Vector2& v)
{
	return v*k;
}
float Dot(const Vector2& a, const Vector2& b)
{
	return Dot(a.vec,b.vec);
}
float Mag(const Vector2& v)
{
	return Mag(v.vec);
}
Vector2 Normalize(const Vector2& v)
{
	return v/Mag(v);
}