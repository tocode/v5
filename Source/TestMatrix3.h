#ifndef TESTMATRIX3_H
#define TESTMATRIX3_H

#include "TestFrame.h"
#include "Matrix3.h"

DEF_CASE2(Matrix3,Operator_float_star)
{
	Matrix3 m(0,1,2,3,4,5,6,7,8);
	float* f = m;
	float r[] = {0,1,2,3,4,5,6,7,8};
	CHECK(r[0]==f[0]);
	CHECK(r[1]==f[1]);
	CHECK(r[2]==f[2]);
	CHECK(r[3]==f[3]);
	CHECK(r[4]==f[4]);
	CHECK(r[5]==f[5]);
	CHECK(r[6]==f[6]);
	CHECK(r[7]==f[7]);
	CHECK(r[8]==f[8]);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Matrix3_default)
{
	Matrix3 m;
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Matrix3_array)
{
	float a[]={	0,1,2,
				3,4,5,
				6,7,8};	
	Matrix3 m(a);
	CHECK(m(1,1)==0);
	CHECK(m(1,2)==1);
	CHECK(m(1,3)==2);
	CHECK(m(2,1)==3);
	CHECK(m(2,2)==4);
	CHECK(m(2,3)==5);
	CHECK(m(3,1)==6);
	CHECK(m(3,2)==7);
	CHECK(m(3,3)==8);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Matrix3_copy)
{	
	Matrix3 m(0,1,2,3,4,5,6,7,8);
	Matrix3 mm(m);
	CHECK(m==mm);
	CASE_SUCCESS;
}

DEF_CASE2(Matrix3,Assign_01)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 b(9,8,7,6,5,4,3,2,1);
	Matrix3 e(9,8,7,6,5,4,3,2,1);
	a=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Assign_02)
{
	Matrix3 r;
	r=Matrix3(0,1,2,3,4,5,6,7,8)+Matrix3(1,1,1,1,1,1,1,1,1);
	Matrix3 e(1,2,3,4,5,6,7,8,9);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_access_const)
{
	Matrix3 m(0,1,2,3,4,5,6,7,8);
	CHECK(m(1,1)==0);
	CHECK(m(2,1)==3);
	CHECK(m(3,1)==6);
	CHECK(m(1,2)==1);
	CHECK(m(2,2)==4);
	CHECK(m(3,2)==7);
	CHECK(m(1,3)==2);
	CHECK(m(2,3)==5);
	CHECK(m(3,3)==8);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_access)
{
	Matrix3 m;
	m(1,1)=0;
	m(2,1)=3;
	m(3,1)=6;
	m(1,2)=1;
	m(2,2)=4;
	m(3,2)=7;
	m(1,3)=2;
	m(2,3)=5;
	m(3,3)=8;
	CHECK(m(1,1)==0);
	CHECK(m(2,1)==3);
	CHECK(m(3,1)==6);
	CHECK(m(1,2)==1);
	CHECK(m(2,2)==4);
	CHECK(m(3,2)==7);
	CHECK(m(1,3)==2);
	CHECK(m(2,3)==5);
	CHECK(m(3,3)==8);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_eq)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 b(0,1,2,3,4,5,6,7,8);
	Matrix3 c(8,7,6,5,4,3,2,1,0);
	CHECK(a==b);
	CHECK(b==a);
	CHECKNOT(a==c);
	CHECKNOT(c==a);
	CHECKNOT(b==c);
	CHECKNOT(c==b);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_ne)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 b(0,1,2,3,4,5,6,7,8);
	Matrix3 c(8,7,6,5,4,3,2,1,0);
	CHECKNOT(a!=b);
	CHECKNOT(b!=a);
	CHECK(a!=c);
	CHECK(c!=a);
	CHECK(b!=c);
	CHECK(c!=b);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_add)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 b(0,1,2,3,4,5,6,7,8);
	Matrix3 e(0,2,4,6,8,10,12,14,16);
	CHECK(a+b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_sub)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 b(8,7,6,5,4,3,2,1,0);
	Matrix3 e(-8,-6,-4,-2,0,2,4,6,8);
	Matrix3 r;
	CHECK(a-b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_negative)
{
	Matrix3 a(1,2,3,4,5,6,7,8,9);
	Matrix3 e(-1,-2,-3,-4,-5,-6,-7,-8,-9);
	CHECK(-a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_mul_Mk)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 e(0,2,4,6,8,10,12,14,16);
	float k=2;
	CHECK(a*k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_div)
{
	Matrix3 a(0,5,15,20,25,30,0,0,0);
	Matrix3 e(0,1,3,4,5,6,0,0,0);
	float k=5;
	CHECK(a/5==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_add_assign)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 b(8,7,6,5,4,3,2,1,0);
	Matrix3 e(8,8,8,8,8,8,8,8,8);
	a+=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_sub_assign)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 b(8,7,6,5,4,3,2,1,0);
	Matrix3 e(-8,-6,-4,-2,0,2,4,6,8);
	a-=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_mul_assign)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 e(0,2,4,6,8,10,12,14,16);
	float k=2;
	a*=k;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_div_assign)
{
	Matrix3 a(	0,5,10,
				15,20,25,
				0,0,0);
	Matrix3 e(	0,1,2,
				3,4,5,
				0,0,0);
	float k=5;
	a/=k;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,RowNum)
{
	Matrix3 m;
	CHECK(m.RowNum()==3);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,ColumnNum)
{
	Matrix3 m;
	CHECK(m.ColumnNum()==3);
	CASE_SUCCESS;
}

// ***** non member function *****

DEF_CASE2(Matrix3,Operator_mul_kM)
{
	Matrix3 a(0,1,2,3,4,5,6,7,8);
	Matrix3 e(0,2,4,6,8,10,12,14,16);
	float k=2;
	CHECK(k*a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Operator_mul)
{
	Matrix3 a(	0,1,2,
				3,4,5,
				0,0,0);
	Matrix3 b(	0,1,2,
				0,1,2,
				0,1,2);
	Matrix3 e(	0,3,6,
				0,12,24,
				0,0,0);
	CHECK(a*b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Transpose)
{
	Matrix3 m(	0,1,2,
				3,4,5,
				6,7,8);
	Matrix3 e(	0,3,6,
				1,4,7,
				2,5,8);
	CHECK(Transpose(m)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Det)
{
	Matrix3 m(	1,0,0,
				0,2,3,
				0,4,5);
	CHECK(Det(m)==-2);
	CASE_SUCCESS;
}
/*
TEST(Matrx3,cofactor)
{
	Matrix3 m(	0,1,2,
				3,4,5,
				6,7,8);
	float e00[]={4,5,7,8};
	float e10[]={1,2,7,8};
	float e11[]={0,2,6,8};
	float e21[]={0,2,3,5};
	float e22[]={0,1,3,4};
	Matrix<float,2,2> c00(e00);
	Matrix<float,2,2> c10(e10);
	Matrix<float,2,2> c11(e11);
	Matrix<float,2,2> c21(e21);
	Matrix<float,2,2> c22(e22);
	CHECK(cofactor(m,0,0)==c00);
	CHECK(cofactor(m,1,0)==c10);
	CHECK(cofactor(m,1,1)==c11);
	CHECK(cofactor(m,2,1)==c21);
	CHECK(cofactor(m,2,2)==c22);
}*/
DEF_CASE2(Matrix3,AlgebraCofactor)
{
	Matrix3 m(	0,1,2,
				3,4,5,
				6,7,8);
	CHECK(AlgebraCofactor(m,1,1)==-3);
	CHECK(AlgebraCofactor(m,2,1)==6);
	CHECK(AlgebraCofactor(m,2,2)==-12);
	CHECK(AlgebraCofactor(m,3,2)==6);
	CHECK(AlgebraCofactor(m,3,3)==-3);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Adj)
{
	Matrix3 a(	-4,-3,3,
				0,2,-2,
				1,4,-1);
	Matrix3 e(	6,9,0,
				-2,1,-8,
				-2,13,-8);
	CHECK(Adj(a)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix3,Inverse)
{
	Matrix3 a(	-4,-3,3,
				0,2,-2,
				1,4,-1);
	Matrix3 e(	6.0/(-24),		9.0/(-24),		0/(-24),
				-2.0/(-24),		1.0/(-24),		-8.0/(-24),
				-2.0/(-24),		13.0/(-24),		-8.0/(-24));
	for (int i=1; i<=3; i++)
		for (int j=1; j<=3; j++)
			CHECK(Inverse(a)(i,j)==e(i,j));
	CASE_SUCCESS;
}

#endif

