#include "Matrix2.h"
#include <stdio.h>

//construction and destruction
Matrix2::Matrix2()
{
}
Matrix2::Matrix2(const float* a)
{
	mat=Matrix<float,2,2>(a);
}
Matrix2::Matrix2(const Matrix2& m)
{
	mat=m.mat;
}
Matrix2::Matrix2(float tm11, float tm12, float tm21, float tm22)
{
	mat(1,1)=tm11;
	mat(1,2)=tm12;
	mat(2,1)=tm21;
	mat(2,2)=tm22;	
}

//assign operation
Matrix2& Matrix2::operator=(const Matrix2& m)
{
	mat=m.mat;
	return *this;
}

//access operation
float  Matrix2::operator()(int i, int j) const
{
	return mat(i,j);
}
float& Matrix2::operator()(int i, int j)
{
	return mat(i,j);
}

//comparison operation
bool operator==(const Matrix2& a, const Matrix2& b)
{
	return a.mat==b.mat;
}
bool operator!=(const Matrix2& a, const Matrix2& b)
{
	return a.mat!=b.mat;
}

//arithematic operations
Matrix2 operator+(const Matrix2& a, const Matrix2& b)
{
	Matrix2 r;
	r.mat = a.mat + b.mat;
	return r;
}
Matrix2 operator-(const Matrix2& a, const Matrix2& b)
{
	Matrix2 r;
	r.mat = a.mat - b.mat;
	return r;
}
Matrix2 Matrix2::operator-() const
{
	Matrix2 r;
	r.mat = -mat;
	return r;
}
Matrix2 operator*(const Matrix2& m, const float k)
{
	Matrix2 r;
	r.mat = m.mat * k;
	return r;
}
Matrix2 operator/(const Matrix2& m, const float k)
{
	Matrix2 r;
	r.mat = m.mat / k;
	return r;
}
Matrix2& Matrix2::operator+=(const Matrix2& m)
{
	mat+=m.mat;
	return *this;
}
Matrix2& Matrix2::operator-=(const Matrix2& m)
{
	mat-=m.mat;
	return *this;
}
Matrix2& Matrix2::operator*=(const float k)
{
	mat*=k;
	return *this;
}
Matrix2& Matrix2::operator/=(const float k)
{
	mat/=k;
	return *this;
}



// k*M
Matrix2 operator*(const float k, const Matrix2& m)
{
	Matrix2 r;
	r = m * k;
	return r;
}

// A*B
Matrix2 operator*(const Matrix2& a, const Matrix2& b)
{
	Matrix2 r;
	r.mat = a.mat * b.mat;
	return r;
}

// M^T
Matrix2 Transpose(const Matrix2& m)
{
	Matrix2 r;
	r.mat = Transpose(m.mat);
	return r;
}

// |M|
float Det(const Matrix2& m)
{
	return Det(m.mat);
}

// cofactor
//Matrix2 cofactor(const Matrix2& m, int u, int v);

// algebra cofactor
float AlgebraCofactor(const Matrix2& m, int u, int v)
{
	return AlgebraCofactor(m.mat,u,v);
}

// adj
Matrix2 Adj(const Matrix2& m)
{
	Matrix2 r;
	r.mat = Adj(m.mat);
	return r;
}

// M^-1
Matrix2 Inverse(const Matrix2& m)
{
	Matrix2 r;
	r.mat = Inverse(m.mat);
	return r;
}

void print(const Matrix2& m)
{
	printf("Matrix2 { %f %f, %f %f }\n",m(1,1),m(1,2),m(2,1),m(2,2) );
}