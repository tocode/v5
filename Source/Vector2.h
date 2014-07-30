#ifndef VECTOR2_H
#define VECTOR2_H

#include "Vector.h"

class Vector2
{
public:
	float& X;
	float& Y;

public:
	Vector2();
	explicit			Vector2(float* a);
						Vector2(const Vector2& v);
						Vector2(float x, float y);

	Vector2&			operator=(const Vector2& v);
	float				operator[](int i) const;
	float&				operator[](int i);
	float				operator()(int i) const;
	float&				operator()(int i);

	Vector2				operator-() const;

	Vector2&			operator+=(const Vector2& v);
	Vector2&			operator-=(const Vector2& v);
	Vector2&			operator*=(float k);
	Vector2&			operator/=(float k);

	int					Dimention() { return vec.Dimention(); }
						operator float*() { return (float*)vec.DataPointer(); }

	friend Vector2		operator*(float k, const Vector2& v);
	friend bool			operator==(const Vector2& a,const Vector2& b);
	friend bool			operator!=(const Vector2& a,const Vector2& b);
	friend Vector2		operator+(const Vector2& a,const Vector2& b);
	friend Vector2		operator-(const Vector2& a,const Vector2& b);
	friend Vector2		operator*(const Vector2& v,float k);
	friend Vector2		operator/(const Vector2& v,float k);
	friend float		Dot(const Vector2& a, const Vector2& b);
	friend Vector2		CrossProduct(const Vector2& a, const Vector2& b);
	friend float		Mag(const Vector2& v);
	friend Vector2		Normalize(const Vector2& v);

private:
	Vector<float,2>		vec;
};




#endif