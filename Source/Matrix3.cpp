#include "Matrix3.h"
#include <stdio.h>

//construction and destruction
Matrix3::Matrix3()
{
}
Matrix3::Matrix3(const float* a)
{
	mat=Matrix<float,3,3>(a);
}
Matrix3::Matrix3(const Matrix3& m)
{
	mat=m.mat;
}
Matrix3::Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	mat(1,1)=m11;
	mat(1,2)=m12;
	mat(1,3)=m13;
	mat(2,1)=m21;
	mat(2,2)=m22;
	mat(2,3)=m23;
	mat(3,1)=m31;
	mat(3,2)=m32;
	mat(3,3)=m33;
}

//assign operation
Matrix3& Matrix3::operator=(const Matrix3& m)
{
	mat=m.mat;
	return *this;
}

//access operation
float  Matrix3::operator()(int i, int j) const
{
	return mat(i,j);
}
float& Matrix3::operator()(int i, int j)
{
	return mat(i,j);
}

//comparison operation
bool operator==(const Matrix3& a, const Matrix3& b)
{
	return a.mat==b.mat;
}
bool operator!=(const Matrix3& a, const Matrix3& b)
{
	return a.mat!=b.mat;
}

//arithematic operations
Matrix3 operator+(const Matrix3& a, const Matrix3& b)
{
	Matrix3 r;
	r.mat = a.mat + b.mat;
	return r;
}
Matrix3 operator-(const Matrix3& a, const Matrix3& b)
{
	Matrix3 r;
	r.mat = a.mat - b.mat;
	return r;
}
Matrix3 Matrix3::operator-() const
{
	Matrix3 r;
	r.mat = -mat;
	return r;
}
Matrix3 operator*(const Matrix3& m, const float k)
{
	Matrix3 r;
	r.mat = m.mat * k;
	return r;
}
Matrix3 operator/(const Matrix3& m, const float k)
{
	Matrix3 r;
	r.mat = m.mat / k;
	return r;
}
Matrix3& Matrix3::operator+=(const Matrix3& m)
{
	mat+=m.mat;
	return *this;
}
Matrix3& Matrix3::operator-=(const Matrix3& m)
{
	mat-=m.mat;
	return *this;
}
Matrix3& Matrix3::operator*=(const float k)
{
	mat*=k;
	return *this;
}
Matrix3& Matrix3::operator/=(const float k)
{
	mat/=k;
	return *this;
}

Vector3 Matrix3::Row(int i) const
{
	return Vector3(mat(i,1),mat(i,2),mat(i,3));
}
Vector3	Matrix3::Column(int j) const
{
	return Vector3(mat(1,j),mat(2,j),mat(3,j));
}
int	Matrix3::RowNum() const 
{ 
	return mat.RowNum(); 
}
int Matrix3::ColumnNum() const 
{ 
	return mat.ColumnNum(); 
}

// k*M
Matrix3 operator*(const float k, const Matrix3& m)
{
	Matrix3 r;
	r = m * k;
	return r;
}

// A*B
Matrix3 operator*(const Matrix3& a, const Matrix3& b)
{
	Matrix3 r;
	r.mat = a.mat * b.mat;
	return r;
}

// M^T
Matrix3 Transpose(const Matrix3& m)
{
	Matrix3 r;
	r.mat = Transpose(m.mat);
	return r;
}

// |M|
float Det(const Matrix3& m)
{
	return Det(m.mat);
}

// cofactor
//Matrix2 cofactor(const Matrix3& m, int u, int v);

// algebra cofactor
float AlgebraCofactor(const Matrix3& m, int u, int v)
{
	return AlgebraCofactor(m.mat,u,v);
}

// adj
Matrix3 Adj(const Matrix3& m)
{
	Matrix3 r;
	r.mat = Adj(m.mat);
	return r;
}

// M^-1
Matrix3 Inverse(const Matrix3& m)
{
	Matrix3 r;
	r.mat = Inverse(m.mat);
	return r;
}

void print(const Matrix3& m)
{
	printf("Matrix3 { %f %f %f, %f %f %f, %f %f %f, %f %f %f }\n",m(1,1),m(1,2),m(1,3),m(2,1),m(2,2),m(2,3),m(3,1),m(3,2),m(3,3) );
}