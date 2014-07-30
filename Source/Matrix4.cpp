#include "Matrix4.h"
#include <stdio.h>

//construction and destruction
Matrix4::Matrix4()
{
}
Matrix4::Matrix4(const float* a)
{
	mat=Matrix<float,4,4>(a);
}
Matrix4::Matrix4(const Matrix4& m)
{
	mat=m.mat;
}
Matrix4::Matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	mat(1,1)=m11;
	mat(1,2)=m12;
	mat(1,3)=m13;
	mat(1,4)=m14;
	mat(2,1)=m21;
	mat(2,2)=m22;
	mat(2,3)=m23;
	mat(2,4)=m24;
	mat(3,1)=m31;
	mat(3,2)=m32;
	mat(3,3)=m33;
	mat(3,4)=m34;
	mat(4,1)=m41;
	mat(4,2)=m42;
	mat(4,3)=m43;
	mat(4,4)=m44;
}

Matrix4::Matrix4(const Matrix3& m3)
{
	for (int i=1; i<=3; i++)
		for (int j=1; j<=3; j++)
			mat(i,j) = m3(i,j);
};

//assign operation
Matrix4& Matrix4::operator=(const Matrix4& m)
{
	mat=m.mat;
	return *this;
}

//access operation
float  Matrix4::operator()(int i, int j) const
{
	return mat(i,j);
}
float& Matrix4::operator()(int i, int j)
{
	return mat(i,j);
}

//comparison operation
bool operator==(const Matrix4& a, const Matrix4& b)
{
	return a.mat==b.mat;
}
bool operator!=(const Matrix4& a, const Matrix4& b)
{
	return a.mat!=b.mat;
}

//arithematic operations
Matrix4 operator+(const Matrix4& a, const Matrix4& b)
{
	Matrix4 r;
	r.mat = a.mat + b.mat;
	return r;
}
Matrix4 operator-(const Matrix4& a, const Matrix4& b)
{
	Matrix4 r;
	r.mat = a.mat - b.mat;
	return r;
}
Matrix4 Matrix4::operator-() const
{
	Matrix4 r;
	r.mat = -mat;
	return r;
}
Matrix4 operator*(const Matrix4& m, const float k)
{
	Matrix4 r;
	r.mat = m.mat * k;
	return r;
}
Matrix4 operator/(const Matrix4& m, const float k)
{
	Matrix4 r;
	r.mat = m.mat / k;
	return r;
}
Matrix4& Matrix4::operator+=(const Matrix4& m)
{
	mat+=m.mat;
	return *this;
}
Matrix4& Matrix4::operator-=(const Matrix4& m)
{
	mat-=m.mat;
	return *this;
}
Matrix4& Matrix4::operator*=(const float k)
{
	mat*=k;
	return *this;
}
Matrix4& Matrix4::operator/=(const float k)
{
	mat/=k;
	return *this;
}
Vector4	Matrix4::Row(int i) const
{ 
	return Vector4(mat(i,1),mat(i,2),mat(i,3),mat(i,4)); 
}
Vector4	Matrix4::Column(int j) const
{
	return Vector4(mat(1,j),mat(2,j),mat(3,j),mat(4,j));
}


Matrix4 operator*(const float k, const Matrix4& m)
{
	Matrix4 r;
	r = m * k;
	return r;
}
// A*B
Matrix4 operator*(const Matrix4& a, const Matrix4& b)
{
	Matrix4 r;
	r.mat = a.mat * b.mat;
	return r;
}
// M^T
Matrix4 Transpose(const Matrix4& m)
{
	Matrix4 r;
	r.mat = Transpose(m.mat);
	return r;
}
// |M|
float Det(const Matrix4& m)
{
	return Det(m.mat);
}
// cofactor
//Matrix2 cofactor(const Matrix4& m, int u, int v);

// algebra cofactor
float AlgebraCofactor(const Matrix4& m, int u, int v)
{
	return AlgebraCofactor(m.mat,u,v);
}
// adj
Matrix4 Adj(const Matrix4& m)
{
	Matrix4 r;
	r.mat = Adj(m.mat);
	return r;
}
// M^-1
Matrix4 Inverse(const Matrix4& m)
{
	Matrix4 r;
	r.mat = Inverse(m.mat);
	return r;
}
void Print(const Matrix4& m)
{
	printf("Matrix4\n %.2f %.2f %.2f %.2f,\n %.2f %.2f %.2f %.2f,\n %.2f %.2f %.2f %.2f,\n %.2f %.2f %.2f %.2f \n",m(1,1),m(1,2),m(1,3),m(1,4),m(2,1),m(2,2),m(2,3),m(2,4),m(3,1),m(3,2),m(3,3),m(3,4),m(4,1),m(4,2),m(4,3),m(4,4) );
}