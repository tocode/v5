#ifndef MATRIX4_H
#define MATRIX4_H

#include "Matrix.h"
#include "Matrix3.h"
#include "Vector4.h"

class Matrix4
{
public:
						Matrix4();
	explicit			Matrix4(const float* a);
						Matrix4(const Matrix4& m);
						Matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);
						Matrix4(const Matrix3& m3);

	Matrix4&			operator=(const Matrix4& m);
	float				operator()(int i, int j) const;
	float&				operator()(int i, int j);

	Matrix4				operator-() const;

	Matrix4&			operator+=(const Matrix4& m);
	Matrix4&			operator-=(const Matrix4& m);
	Matrix4&			operator*=(const float k);
	Matrix4&			operator/=(const float k);

	
	Vector4				Row(int i) const;
	Vector4				Column(int j) const;
	int					RowNum() const { return mat.RowNum(); }
	int					ColumnNum() const { return mat.ColumnNum(); }
						operator float*() {	return (float*)mat.DataPointer(); }

	friend bool			operator==(const Matrix4& a, const Matrix4& b);
	friend bool			operator!=(const Matrix4& a, const Matrix4& b);
	friend Matrix4				operator*(const float k, const Matrix4& m);
	friend Matrix4		operator+(const Matrix4& a, const Matrix4& b);
	friend Matrix4		operator-(const Matrix4& a, const Matrix4& b);
	friend Matrix4		operator*(const Matrix4& m, const float k);
	friend Matrix4		operator/(const Matrix4& m, const float k);
	friend Matrix4		operator*(const Matrix4& a, const Matrix4& b);
	friend Matrix4		Transpose(const Matrix4& m);
	friend float		Det(const Matrix4& m);
	friend float		AlgebraCofactor(const Matrix4& m, int u, int v);
	friend Matrix4		Adj(const Matrix4& m);
	friend Matrix4		Inverse(const Matrix4& m);
	friend void			Print(const Matrix4& m);

private:
	Matrix<float,4,4>	mat;
};


#endif