#ifndef TESTMATRIX_H
#define TESTMATRIX_H

#include "TestFrame.h"
#include "Matrix.h"

DEF_CASE2(Matrix,Matrix)
{
	Matrix<float,4,4> m;
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Matrix_array)
{
	float a[]={	0,1,2,
		3,4,5,
		6,7,8};	
	Matrix<float,3,3> m(a);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Matrix_copy)
{
	float a[]={	0,1,2,
		3,4,5,
		6,7,8};	
	Matrix<float,3,3> m(a);
	Matrix<float,3,3> mm(m);
	CHECK(m==mm);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Assign)
{
	float a[]={	0,1,2,
				3,4,5,
				6,7,8};	
	float b[]={	9,8,7,
				6,5,4,
				3,2,1};
	float e[]={	9,8,7,
				6,5,4,
				3,2,1};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> mb(b);
	Matrix<float,3,3> me(e);
	ma=mb;
	CHECK(ma==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_access_const)
{
	float a[]={	0,1,2,
				3,4,5,
				6,7,8};	
	Matrix<float,3,3> m(a);
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
DEF_CASE2(Matrix,Operator_access)
{
	Matrix<float,3,3> m;
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
DEF_CASE2(Matrix,Operator_eq)
{
	float a[]={	0,1,2,
				3,4,5,
				6,7,8};	
	float b[]={	0,1,2,
				3,4,5,
				6,7,8};
	float c[]={	9,8,7,
				6,5,4,
				3,2,1};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> mb(b);
	Matrix<float,3,3> mc(c);
	CHECK(ma==mb);
	CHECK(mb==ma);
	CHECKNOT(ma==mc);
	CHECKNOT(mc==ma);
	CHECKNOT(mb==mc);
	CHECKNOT(mc==mb);

	float a1[]={0};
	float a2[]={-0};
	Matrix<float,1,1> ma1(a1);
	Matrix<float,1,1> ma2(a2);
	CHECK(ma1==ma2);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_ne)
{
	float a[]={	0,1,2,
				3,4,5,
				6,7,8};	
	float b[]={	0,1,2,
				3,4,5,
				6,7,8};
	float c[]={	9,8,7,
				6,5,4,
				3,2,1};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> mb(b);
	Matrix<float,3,3> mc(c);

	CHECKNOT(ma!=mb);
	CHECKNOT(mb!=ma);
	CHECK(ma!=mc);
	CHECK(mc!=ma);
	CHECK(mb!=mc);
	CHECK(mc!=mb);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_add)
{
	float a[]={	0,1,2,
				3,4,5,
				6,7,8};	
	float b[]={	9,8,7,
				6,5,4,
				3,2,1};
	float r[]={	0	};
	float e[]={	9,9,9,
				9,9,9,
				9,9,9};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> mb(b);
	Matrix<float,3,3> mr(r);
	Matrix<float,3,3> me(e);
	mr=ma+mb;
	CHECK(mr==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_sub)
{
	float a[]={	0,1,2,
				3,4,5,
				6,7,8};	
	float b[]={	9,8,7,
				6,5,4,
				3,2,1};
	float r[]={0};
	float e[]={	-9,-7,-5,
				-3,-1,1,
				3,5,7};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> mb(b);
	Matrix<float,3,3> mr(r);
	Matrix<float,3,3> me(e);
	mr=ma-mb;
	CHECK(mr==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_negative)
{
	float a[]={	0,1,2,3,4,5,6,7,8};	
	float e[9];
	for (int i=0; i<9; i++) e[i]=-a[i];
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> me(e);
	Matrix<float,3,3> mr(-ma);
	CHECK(mr==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_mul_Mk)
{
	float a[]={	0,1,2,
				3,4,5};
	float e[]={	0,2,4,
				6,8,10};
	Matrix<float,2,3> ma(a);
	Matrix<float,2,3> me(e);
	float k=2;
	Matrix<float,2,3> mr(ma*k);
	CHECK(mr==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_div)
{
	float a[]={	0,5,15,
				20,25,30};
	float e[]={	0,1,3,
				4,5,6};
	Matrix<float,2,3> ma(a);
	Matrix<float,2,3> me(e);
	float k=5;
	Matrix<float,2,3> mr(ma/k);
	CHECK(mr==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_add_assign)
{
	float a[]={	0,1,2,
		3,4,5,
		6,7,8};	
	float b[]={	9,8,7,
		6,5,4,
		3,2,1};
	float e[]={	9,9,9,
		9,9,9,
		9,9,9};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> mb(b);
	Matrix<float,3,3> me(e);
	ma+=mb;
	CHECK(ma==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_sub_assign)
{
	float a[]={	0,1,2,
		3,4,5,
		6,7,8};	
	float b[]={	9,8,7,
		6,5,4,
		3,2,1};
	float e[]={	-9,-7,-5,
		-3,-1,1,
		3,5,7};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> mb(b);
	Matrix<float,3,3> me(e);
	ma-=mb;
	CHECK(ma==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_mul_assign)
{
	float a[]={	0,1,2,
				3,4,5};
	float e[]={	0,2,4,
				6,8,10};
	Matrix<float,2,3> ma(a);
	Matrix<float,2,3> me(e);
	float k=2;
	ma*=k;
	CHECK(ma==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_div_assign)
{
	float a[]={	0,5,10,
				15,20,25};
	float e[]={	0,1,2,
				3,4,5};
	Matrix<float,2,3> ma(a);
	Matrix<float,2,3> me(e);
	float k=5;
	ma/=k;
	CHECK(ma==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,RowNum)
{
	Matrix<float,5,7> m;
	CHECK(m.RowNum()==5);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,ColumnNum)
{
	Matrix<float,5,7> m;
	CHECK(m.ColumnNum()==7);
	CASE_SUCCESS;
}

// ***** non member function *****

DEF_CASE2(Matrix,Operator_mul_kM)
{
	float a[]={	0,1,2,
				3,4,5};
	float e[]={	0,2,4,
				6,8,10};
	Matrix<float,2,3> ma(a);
	Matrix<float,2,3> me(e);
	float k=2;
	Matrix<float,2,3> mr(k*ma);
	CHECK(mr==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Operator_mul)
{
	float a[]={	0,1,2,
				3,4,5};
	float b[]={	0,1,2,3,
				4,5,6,7,
				8,9,0,1};
	float e[]={	20,23,6,9,
				56,68,30,42};
	Matrix<float,2,3> ma(a);
	Matrix<float,3,4> mb(b);
	Matrix<float,2,4> me(e);
	Matrix<float,2,4> mr(ma*mb);
	CHECK(mr==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Transpose)
{
	float a[]={ 0,1,2,
				3,4,5,
				6,7,8};
	float e[]={	0,3,6,
				1,4,7,
				2,5,8};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> me(e);
	CHECK(Transpose(ma)==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Cofactor)
{
	float a[]={ 0,1,2,
				3,4,5,
				6,7,8};
	float e00[]={4,5,7,8};
	float e10[]={1,2,7,8};
	float e11[]={0,2,6,8};
	float e21[]={0,2,3,5};
	float e22[]={0,1,3,4};
	Matrix<float,3,3> m(a);
	Matrix<float,2,2> c00(e00);
	Matrix<float,2,2> c10(e10);
	Matrix<float,2,2> c11(e11);
	Matrix<float,2,2> c21(e21);
	Matrix<float,2,2> c22(e22);
	CHECK(Cofactor(m,1,1)==c00);
	CHECK(Cofactor(m,2,1)==c10);
	CHECK(Cofactor(m,2,2)==c11);
	CHECK(Cofactor(m,3,2)==c21);
	CHECK(Cofactor(m,3,3)==c22);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,AlgebraCofactor)
{
	float a[]={ 0,1,2,
				3,4,5,
				6,7,8};
	Matrix<float,3,3> m(a);
	CHECK(AlgebraCofactor(m,1,1)==-3);
	CHECK(AlgebraCofactor(m,2,1)==6);
	CHECK(AlgebraCofactor(m,2,2)==-12);
	CHECK(AlgebraCofactor(m,3,2)==6);
	CHECK(AlgebraCofactor(m,3,3)==-3);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Det)
{
	float a[]={ 1,0,0,
		0,2,3,
		0,4,5};
	Matrix<float,3,3> m(a);
	CHECK(Det(m)==-2);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Adj)
{
	float a[]={ -4,-3,3,
				0,2,-2,
				1,4,-1};
	float e[]={ 6,9,0,
				-2,1,-8,
				-2,13,-8};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> me(e);
	CHECK(Adj(ma)==me);
	CASE_SUCCESS;
}
DEF_CASE2(Matrix,Inverse)
{
	float a[]={ -4,-3,3,
		0,2,-2,
		1,4,-1};
	float e[]={ 6.0/(-24),		9.0/(-24),		0.0/(-24),
				-2.0/(-24),		1.0/(-24),		-8.0/(-24),
				-2.0/(-24),		13.0/(-24),		-8.0/(-24)};
	Matrix<float,3,3> ma(a);
	Matrix<float,3,3> me(e);
	CHECK(Inverse(ma)==me);
	CASE_SUCCESS;
}

#endif