#ifndef MATRIX2_H
#define MATRIX2_H

#include "Matrix.h"

class Matrix2
{
public:
	Matrix2();
	explicit			Matrix2(const float* a);
						Matrix2(const Matrix2& m);
						Matrix2(float tm11, float tm12, float tm21, float tm22);

	Matrix2&			operator=(const Matrix2& m);
	float				operator()(int i, int j) const;
	float&				operator()(int i, int j);

	Matrix2				operator-() const;

	Matrix2&			operator+=(const Matrix2& m);
	Matrix2&			operator-=(const Matrix2& m);
	Matrix2&			operator*=(const float k);
	Matrix2&			operator/=(const float k);

	int					RowNum() const { return mat.RowNum(); }
	int					ColumnNum() const { return mat.ColumnNum(); }
						operator float*() { return (float*)mat.DataPointer(); }

	friend Matrix2		operator*(const float k, const Matrix2& m);
	friend bool			operator==(const Matrix2& a, const Matrix2& b);
	friend bool			operator!=(const Matrix2& a, const Matrix2& b);
	friend Matrix2		operator*(const float k, const Matrix2& m);
	friend Matrix2		operator+(const Matrix2& a, const Matrix2& b);
	friend Matrix2		operator-(const Matrix2& a, const Matrix2& b);
	friend Matrix2		operator*(const Matrix2& m, const float k);
	friend Matrix2		operator/(const Matrix2& m, const float k);
	friend Matrix2		operator*(const Matrix2& a, const Matrix2& b);
	friend Matrix2		Transpose(const Matrix2& m);
	friend float		Det(const Matrix2& m);
	friend float		AlgebraCofactor(const Matrix2& m, int u, int v);
	friend Matrix2		Adj(const Matrix2& m);
	friend Matrix2		Inverse(const Matrix2& m);

private:
	Matrix<float,2,2>	mat;
};


#endif