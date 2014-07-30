#ifndef MATRIX3_H
#define MATRIX3_H

#include "Matrix.h"
#include "Vector3.h"

class Matrix3
{
public:
	Matrix3();
	explicit			Matrix3(const float* a);
	Matrix3(const Matrix3& m);
	Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);

	Matrix3&			operator=(const Matrix3& m);
	float				operator()(int i, int j) const;
	float&				operator()(int i, int j);

	Matrix3				operator-() const;

	Matrix3&			operator+=(const Matrix3& m);
	Matrix3&			operator-=(const Matrix3& m);
	Matrix3&			operator*=(const float k);
	Matrix3&			operator/=(const float k);

	Vector3				Row(int i) const;
	Vector3				Column(int j) const;
	int					RowNum() const;
	int					ColumnNum() const;
						operator float*() { return (float*)mat.DataPointer(); }

	friend Matrix3		operator*(const float k, const Matrix3& m);
	friend bool			operator==(const Matrix3& a, const Matrix3& b);
	friend bool			operator!=(const Matrix3& a, const Matrix3& b);
	friend Matrix3		operator*(const float k, const Matrix3& m);
	friend Matrix3		operator+(const Matrix3& a, const Matrix3& b);
	friend Matrix3		operator-(const Matrix3& a, const Matrix3& b);
	friend Matrix3		operator*(const Matrix3& m, const float k);
	friend Matrix3		operator/(const Matrix3& m, const float k);
	friend Matrix3		operator*(const Matrix3& a, const Matrix3& b);
	friend Matrix3		Transpose(const Matrix3& m);
	friend float		Det(const Matrix3& m);
	friend float		AlgebraCofactor(const Matrix3& m, int u, int v);
	friend Matrix3		Adj(const Matrix3& m);
	friend Matrix3		Inverse(const Matrix3& m);

private:
	Matrix<float,3,3>	mat;
};


#endif