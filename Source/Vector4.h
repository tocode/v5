#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector.h"
#include "Vector3.h"

class Vector4
{
public:
	float& X;
	float& Y;
	float& Z;
	float& W;

public:
						Vector4();
	explicit			Vector4(float* a);
						Vector4(const Vector4& v);
						Vector4(float x, float y, float z, float w);
						Vector4(const Vector3& v3, const float tw);

	Vector4&			operator=(const Vector4& v);
	float				operator[](int i) const;
	float&				operator[](int i);
	float				operator()(int i) const;
	float&				operator()(int i);
	Vector3				XYZ() const;

	Vector4				operator-() const;
	Vector4&			operator+=(const Vector4& v);
	Vector4&			operator-=(const Vector4& v);
	Vector4&			operator*=(float k);
	Vector4&			operator/=(float k);

	int					Dimention() { return vec.Dimention(); }
						operator float*() { return (float*)vec.DataPointer(); }

	friend Vector4		operator*(float k, const Vector4& v);
	friend bool			operator==(const Vector4& a,const Vector4& b);
	friend bool			operator!=(const Vector4& a,const Vector4& b);
	friend Vector4		operator+(const Vector4& a,const Vector4& b);
	friend Vector4		operator-(const Vector4& a,const Vector4& b);
	friend Vector4		operator*(const Vector4& v,float k);
	friend Vector4		operator/(const Vector4& v,float k);
	friend float		Dot(const Vector4& a, const Vector4& b);
	friend float		Mag(const Vector4& v);
	friend Vector4		Normalize(const Vector4& v);

private:
	Vector<float,4>		vec;
};


#endif