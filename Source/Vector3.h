#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector.h"

class Vector3
{
public:
	float& X;
	float& Y;
	float& Z;

public:
	Vector3();
	explicit			Vector3(float* a);
						Vector3(const Vector3& v);
						Vector3(float x, float y, float z);

	Vector3&			operator=(const Vector3& v);
	float				operator[](int i) const;
	float&				operator[](int i);
	float				operator()(int i) const;
	float&				operator()(int i);

	Vector3				operator-() const;

	Vector3&			operator+=(const Vector3& v);
	Vector3&			operator-=(const Vector3& v);
	Vector3&			operator*=(float k);
	Vector3&			operator/=(float k);

	int					Dimention() { return vec.Dimention(); }
						operator float*() { return (float*)vec.DataPointer(); }

	friend Vector3		operator*(float k, const Vector3& v);
	friend bool			operator==(const Vector3& a,const Vector3& b);
	friend bool			operator!=(const Vector3& a,const Vector3& b);
	friend Vector3		operator+(const Vector3& a,const Vector3& b);
	friend Vector3		operator-(const Vector3& a,const Vector3& b);
	friend Vector3		operator*(const Vector3& v,float k);
	friend Vector3		operator/(const Vector3& v,float k);
	friend float		Dot(const Vector3& a, const Vector3& b);
	friend Vector3		CrossProduct(const Vector3& a, const Vector3& b);
	friend float		Mag(const Vector3& v);
	friend Vector3		Normalize(const Vector3& v);

private:
	Vector<float,3>		vec;
};


#endif