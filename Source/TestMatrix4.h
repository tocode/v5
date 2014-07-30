#ifndef TESTMATRIX4_H
#define TESTMATRIX4_H

#include "TestFrame.h"
#include "Matrix3.h"
#include "Matrix4.h"

DEF_CASE2(Matrix4,Operator_float_star)
{
	Matrix4 m(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	float* f = m;
	float r[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	CHECK(r[0]==f[0]);
	CHECK(r[1]==f[1]);
	CHECK(r[2]==f[2]);
	CHECK(r[3]==f[3]);
	CHECK(r[4]==f[4]);
	CHECK(r[5]==f[5]);
	CHECK(r[6]==f[6]);
	CHECK(r[7]==f[7]);
	CHECK(r[8]==f[8]);
	CHECK(r[9]==f[9]);
	CHECK(r[10]==f[10]);
	CHECK(r[11]==f[11]);
	CHECK(r[12]==f[12]);
	CHECK(r[13]==f[13]);
	CHECK(r[14]==f[14]);
	CHECK(r[15]==f[15]);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Matrix4_default)
{
	Matrix4 m;
	CASE_SUCCESS;
}

DEF_CASE2(Matrix4,construction_array)
{
	float a[]={	0,1,2,3,
				4,5,6,7,
				8,9,10,11,
				12,13,14,15};
	Matrix4 m(a);
	CHECK(m(1,1)==0);
	CHECK(m(1,2)==1);
	CHECK(m(1,3)==2);
	CHECK(m(1,4)==3);
	CHECK(m(2,1)==4);
	CHECK(m(2,2)==5);
	CHECK(m(2,3)==6);
	CHECK(m(2,4)==7);
	CHECK(m(3,1)==8);
	CHECK(m(3,2)==9);
	CHECK(m(3,3)==10);
	CHECK(m(3,4)==11);
	CHECK(m(4,1)==12);
	CHECK(m(4,2)==13);
	CHECK(m(4,3)==14);
	CHECK(m(4,4)==15);
	CASE_SUCCESS;
}

DEF_CASE2(Matrix4,Matrix4_copy)
{	
	Matrix4 m(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 mm(m);
	CHECK(m==mm);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Matrix4_from_Matrix3)
{
	Matrix4 m4(Matrix3(1,2,3,4,5,6,7,8,9));
	Matrix4 r4( 1,2,3,0,
				4,5,6,0,
				7,8,9,0,
				0,0,0,0);
	CHECK(m4==r4);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Assign_01)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 b(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
	Matrix4 e(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
	a=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Assign_02)
{
	Matrix4 r;
	r=Matrix4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)+Matrix4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	Matrix4 e(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_access_const)
{
	Matrix4 m(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	CHECK(m(1,1)==0);
	CHECK(m(1,2)==1);
	CHECK(m(1,3)==2);
	CHECK(m(1,4)==3);
	CHECK(m(2,1)==4);
	CHECK(m(2,2)==5);
	CHECK(m(2,3)==6);
	CHECK(m(2,4)==7);
	CHECK(m(3,1)==8);
	CHECK(m(3,2)==9);
	CHECK(m(3,3)==10);
	CHECK(m(3,4)==11);
	CHECK(m(4,1)==12);
	CHECK(m(4,2)==13);
	CHECK(m(4,3)==14);
	CHECK(m(4,4)==15);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_access)
{
	Matrix4 m;
	m(1,1)=0;
	m(1,2)=1;
	m(1,3)=2;
	m(1,4)=3;
	m(2,1)=4;
	m(2,2)=5;
	m(2,3)=6;
	m(2,4)=7;
	m(3,1)=8;
	m(3,2)=9;
	m(3,3)=10;
	m(3,4)=11;
	m(4,1)=12;
	m(4,2)=13;
	m(4,3)=14;
	m(4,4)=15;
	CHECK(m(1,1)==0);
	CHECK(m(1,2)==1);
	CHECK(m(1,3)==2);
	CHECK(m(1,4)==3);
	CHECK(m(2,1)==4);
	CHECK(m(2,2)==5);
	CHECK(m(2,3)==6);
	CHECK(m(2,4)==7);
	CHECK(m(3,1)==8);
	CHECK(m(3,2)==9);
	CHECK(m(3,3)==10);
	CHECK(m(3,4)==11);
	CHECK(m(4,1)==12);
	CHECK(m(4,2)==13);
	CHECK(m(4,3)==14);
	CHECK(m(4,4)==15);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_eq)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 b(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 c(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
	CHECK(a==b);
	CHECK(b==a);
	CHECKNOT(a==c);
	CHECKNOT(c==a);
	CHECKNOT(b==c);
	CHECKNOT(c==b);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_ne)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 b(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 c(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
	CHECKNOT(a!=b);
	CHECKNOT(b!=a);
	CHECK(a!=c);
	CHECK(c!=a);
	CHECK(b!=c);
	CHECK(c!=b);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_add)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 b(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	CHECK(a+b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_sub)
{
	Matrix4 a(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	Matrix4 b(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	CHECK(a-b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_negative)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(-0.0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15);
	CHECK(-a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_mul_Mk)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	float k=2;
	CHECK(a*k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_div)
{
	Matrix4 a(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	Matrix4 e(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	float k=2;
	CHECK(a/k==e);
	CHECK(a/2==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_add_assign)
{
	
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 b(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	a+=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_sub_assign)
{
	Matrix4 a(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	Matrix4 b(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	a-=b;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_mul_assign)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	float k=2;
	a*=k;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_div_assign)
{
	Matrix4 a(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	Matrix4 e(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	float k=2;
	a/=k;
	CHECK(a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,RowNum)
{
	Matrix4 m;
	CHECK(m.RowNum()==4);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,ColumnNum)
{
	Matrix4 m;
	CHECK(m.ColumnNum()==4);
	CASE_SUCCESS;
}

// ***** non member function *****

DEF_CASE2(Matrix4,Operator_mul_kM)
{
	Matrix4 a(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	Matrix4 e(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
	float k=2;
	CHECK(k*a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Operator_mul)
{
	Matrix4 a(0,1,0,2,0,3,0,4,1,0,2,0,3,0,4,0);
	Matrix4 b(2,0,0,3,0,3,1,0,4,2,0,0,0,0,1,4);
	Matrix4 e(0,3,3,8,0,9,7,16,10,4,0,3,22,8,0,9);
	CHECK(a*b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Transpose)
{
	Matrix4 m(	0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15);
	Matrix4 e(	0,4,8,12,
		1,5,9,13,
		2,6,10,14,
		3,7,11,15);
	CHECK(Transpose(m)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Det)
{
	Matrix4 m(	1,0,0,0,
		0,2,3,0,
		0,4,5,0,
		0,0,0,1);
	CHECK(Det(m)==-2);
	CASE_SUCCESS;
}
/*
DEF_CASE2(Matrix4,Cofactor)
{
	Matrix4 m(	0,1,2,0,
				3,4,5,0,
				6,7,8,0,
				0,0,0,1);
	float e00[]={4,5,0,7,8,0,0,0,1};
	float e10[]={1,2,0,7,8,0,0,0,1};
	float e11[]={0,2,0,6,8,0,0,0,1};
	float e21[]={0,2,0,3,5,0,0,0,1};
	float e22[]={0,1,0,3,4,0,0,0,1};
	Matrix<float,3,3> c00(e00);
	Matrix<float,3,3> c10(e10);
	Matrix<float,3,3> c11(e11);
	Matrix<float,3,3> c21(e21);
	Matrix<float,3,3> c22(e22);
	CHECK(Cofactor(m,1,1)==c00);
	CHECK(Cofactor(m,2,1)==c10);
	CHECK(Cofactor(m,2,2)==c11);
	CHECK(Cofactor(m,3,2)==c21);
	CHECK(Cofactor(m,3,3)==c22);
	CASE_SUCCESS;
}*/
DEF_CASE2(Matrix4,AlgebraCofactor)
{
	Matrix4 m(	0,1,2,0,
				3,4,5,0,
				6,7,8,0,
				0,0,0,1);
	CHECK(AlgebraCofactor(m,1,1)==-3);
	CHECK(AlgebraCofactor(m,2,1)==6);
	CHECK(AlgebraCofactor(m,2,2)==-12);
	CHECK(AlgebraCofactor(m,3,2)==6);
	CHECK(AlgebraCofactor(m,3,3)==-3);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Adj)
{
	Matrix4 a(	-4,-3,3,0,
		0,2,-2,0,
		1,4,-1,0,
		0,0,0,1);
	Matrix4 e(	6,9,0,-0.0,
		-2,1,-8,0,
		-2,13,-8,-0.0,
		-0.0,0,-0.0,-24);
	Matrix4 r(Adj(a));
	CHECK(Adj(a)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix4,Inverse)
{
	Matrix4 a(	-4,-3,3,0,
				0,2,-2,0,
				1,4,-1,0,
				0,0,0,1);
	Matrix4 e(	6.0/(-24),		9.0/(-24),		0.0/(-24),		0,
				-2.0/(-24),		1.0/(-24),		-8.0/(-24),		-0.0,
				-2.0/(-24),		13.0/(-24),		-8.0/(-24),		0,
				0,				-0.0,				0,				1);
	for (int i=1; i<=3; i++)
		for (int j=1; j<=3; j++)
			CHECK(Inverse(a)(i,j)==e(i,j));
	CASE_SUCCESS;
}

#endif

