#ifndef TESTMATRIX2_H
#define TESTMATRIX2_H

#include "TestFrame.h"
#include "Matrix2.h"

DEF_CASE2(Matrix2,Operator_float_star)
{
	Matrix2 m(0,1,2,3);
	float* f = m;
	float r[] = {0,1,2,3};
	CHECK(r[0]==f[0]);
	CHECK(r[1]==f[1]);
	CHECK(r[2]==f[2]);
	CHECK(r[3]==f[3]);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Matrix2_default)
{
	Matrix2 m;
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Matrix2_array)
{
	float a[]={	0,1,2,3};	
	Matrix2 m(a);
	CHECK(m(1,1)==0);
	CHECK(m(1,2)==1);
	CHECK(m(2,1)==2);
	CHECK(m(2,2)==3);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Matrix2_copy)
{	
	Matrix2 m(0,1,2,3);
	Matrix2 mm(m);
	CHECK(m==mm);
	CASE_SUCCESS;
}

DEF_CASE2(Matrix2,Assign_01)
{
	Matrix2 a(0,1,2,3);
	Matrix2 b(3,2,1,0);
	Matrix2 e(3,2,1,0);
	a=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Assign_02)
{
	Matrix2 r;
	r=Matrix2(0,1,2,3)+Matrix2(1,1,1,1);
	Matrix2 e(1,2,3,4);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_access_const)
{
	Matrix2 m(0,1,2,3);
	CHECK(m(1,1)==0);
	CHECK(m(2,1)==2);
	CHECK(m(1,2)==1);
	CHECK(m(2,2)==3);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_access)
{
	Matrix2 m;
	m(1,1)=0;
	m(2,1)=3;
	m(1,2)=1;
	m(2,2)=4;
	CHECK(m(1,1)==0);
	CHECK(m(2,1)==3);
	CHECK(m(1,2)==1);
	CHECK(m(2,2)==4);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_eq)
{
	Matrix2 a(0,1,2,3);
	Matrix2 b(0,1,2,3);
	Matrix2 c(3,2,1,0);
	CHECK(a==b);
	CHECK(b==a);
	CHECKNOT(a==c);
	CHECKNOT(c==a);
	CHECKNOT(b==c);
	CHECKNOT(c==b);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_ne)
{
	Matrix2 a(0,1,2,3);
	Matrix2 b(0,1,2,3);
	Matrix2 c(3,2,1,0);
	CHECKNOT(a!=b);
	CHECKNOT(b!=a);
	CHECK(a!=c);
	CHECK(c!=a);
	CHECK(b!=c);
	CHECK(c!=b);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_add)
{
	Matrix2 a(0,1,2,3);
	Matrix2 b(0,1,2,3);
	Matrix2 e(0,2,4,6);
	CHECK(a+b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_sub)
{
	Matrix2 a(0,1,2,3);
	Matrix2 b(8,7,6,5);
	Matrix2 e(-8,-6,-4,-2);
	Matrix2 r;
	CHECK(a-b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_negative)
{
	Matrix2 a(1,2,3,4);
	Matrix2 e(-1,-2,-3,-4);
	CHECK(-a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_mul_Mk)
{
	Matrix2 a(0,1,2,3);
	Matrix2 e(0,2,4,6);
	float k=2;
	CHECK(a*k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_div)
{
	Matrix2 a(0,5,15,20);
	Matrix2 e(0,1,3,4);
	float k=5;
	CHECK(a/5==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_add_assign)
{
	Matrix2 a(0,1,2,3);
	Matrix2 b(8,7,6,5);
	Matrix2 e(8,8,8,8);
	a+=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_sub_assign)
{
	Matrix2 a(0,1,2,3);
	Matrix2 b(8,7,6,5);
	Matrix2 e(-8,-6,-4,-2);
	a-=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_mul_assign)
{
	Matrix2 a(0,1,2,3);
	Matrix2 e(0,2,4,6);
	float k=2;
	a*=k;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_div_assign)
{
	Matrix2 a(0,5,10,15);
	Matrix2 e(0,1,2,3);
	float k=5;
	a/=k;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,RowNum)
{
	Matrix2 m;
	CHECK(m.RowNum()==2);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,ColumnNum)
{
	Matrix2 m;
	CHECK(m.ColumnNum()==2);
	CASE_SUCCESS;
}

// ***** non member function *****

DEF_CASE2(Matrix2,Operator_mul_kM)
{
	Matrix2 a(0,1,2,3);
	Matrix2 e(0,2,4,6);
	float k=2;
	CHECK(k*a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Operator_mul)
{
	Matrix2 a(	0,1,
				2,3);
	Matrix2 b(	3,2,
				1,0);
	Matrix2 e(	1,0,
				9,4);
	CHECK(a*b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Transpose)
{
	Matrix2 m(	0,1,
				2,3);
	Matrix2 e(	0,2,
				1,3);
	CHECK(Transpose(m)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Det)
{
	Matrix2 m(	2,3,
				4,5);
	CHECK(Det(m)==-2);
	CASE_SUCCESS;
}
/*
TEST(Matrx3,cofactor)
{
	Matrix2 m(	0,1,2,
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
DEF_CASE2(Matrix2,AlgebraCofactor)
{
	Matrix2 m(	0,1,
				2,3);
	CHECK(AlgebraCofactor(m,1,1)==3);
	CHECK(AlgebraCofactor(m,2,1)==-1);
	CHECK(AlgebraCofactor(m,2,2)==0);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Adj)
{
	Matrix2 a(	0,1,
				2,3);
	Matrix2 e(	3,-1,
				-2,0);
	CHECK(Adj(a)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix2,Inverse)
{
	Matrix2 a(0,1,2,3);
	Matrix2 e(-1.5,0.5,1,0);
	for (int i=1; i<=2; i++)
		for (int j=1; j<=2; j++)
			CHECK(Inverse(a)(i,j)==e(i,j));
	CASE_SUCCESS;
}

#endif

