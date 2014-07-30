#ifndef TESTVECTOR4_H
#define TESTVECTOR4_H

#include "TestFrame.h"
#include "Vector3.h"
#include "Vector4.h"

DEF_CASE2(Vector4,Operator_float_star)
{
	Vector4 v(1,2,3,4);
	float* f = v;
	float r[] = {1,2,3,4};
	CHECK(r[0]==f[0]);
	CHECK(r[1]==f[1]);
	CHECK(r[2]==f[2]);
	CHECK(r[3]==f[3]);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,construction_default)
{
	Vector4 v;
	CHECK(v.X==0);
	CHECK(v.Y==0);
	CHECK(v.Z==0);
	CHECK(v.W==0);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,construction_array)
{
	float a[]={0,1,2,3};
	Vector4 v(a);
	CHECK(v.X==0);
	CHECK(v.Y==1);
	CHECK(v.Z==2);
	CHECK(v.W==3);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,construction_copy)
{
	Vector4 v(1,2,3,4);
	Vector4 e(1,2,3,4);
	Vector4 r(v);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,construction_from_Vector3)
{
	Vector4 v4(Vector3(1,2,3),4);
	Vector4 r4(1,2,3,4);
	CHECK(v4==r4);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,assign)
{
	Vector4 v(1,2,3,4);
	Vector4 e(1,2,3,4);
	Vector4 r;
	r=v;
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_index_const)
{
	Vector4 v(1,2,3,4);
	CHECK(v[0]==1);
	CHECK(v[1]==2);
	CHECK(v[2]==3);	
	CHECK(v[3]==4);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_index)
{
	Vector4 v;
	Vector4 e(1,2,3,4);
	v[0]=1;
	v[1]=2;
	v[2]=3;
	v[3]=4;
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_math_index_const)
{
	Vector4 v(1,2,3,4);
	CHECK(v(1)==1);
	CHECK(v(2)==2);
	CHECK(v(3)==3);	
	CHECK(v(4)==4);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_math_index)
{
	Vector4 v;
	Vector4 e(1,2,3,4);
	v(1)=1;
	v(2)=2;
	v(3)=3;
	v(4)=4;
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_eq)
{
	Vector4 a(1,2,3,4);
	Vector4 b(1,2,3,4);
	CHECK(a==b);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_ne)
{
	Vector4 a(1,2,3,4);
	Vector4 b(0,1,2,3);
	CHECK(a!=b);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_add)
{
	Vector4 a(1,2,3,4);
	Vector4 b(4,5,6,7);
	Vector4 e(5,7,9,11);
	CHECK(a+b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_sub)
{
	Vector4 a(9,8,7,6);
	Vector4 b(1,2,3,4);
	Vector4 e(8,6,4,2);
	CHECK(a-b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_negative)
{
	Vector4 a(1,2,3,4);
	Vector4 e(-1,-2,-3,-4);
	CHECK(-a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_mul_Vk)
{
	Vector4 v(1,2,3,4);
	float k=3;
	Vector4 e(3,6,9,12);
	CHECK(v*k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_div)
{
	Vector4 v(3,6,9,0);
	float k=3;
	Vector4 e(1,2,3,0);
	CHECK(v/k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_reflexive_add)
{
	Vector4 v(1,2,3,4);
	v+=Vector4(5,6,-7,2);
	Vector4 e(6,8,-4,6);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_reflexive_sub)
{
	Vector4 v(5,6,7,8);
	v-=Vector4(1,-9,2,3);
	Vector4 e(4,15,5,5);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_reflexive_mul)
{
	Vector4 v(1,2,3,4);
	v*=3;
	Vector4 e(3,6,9,12);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Operator_reflexive_div)
{
	Vector4 v(3,6,9,3);
	v/=3;
	Vector4 e(1,2,3,1);
	CHECK(v==e);
	CASE_SUCCESS;
}

// ***** NON MEMBER FUNCTION *****

DEF_CASE2(Vector4,Operator_mul_kV)
{
	Vector4 v(1,2,3,4);
	float k=3;
	Vector4 e(3,6,9,12);
	CHECK(k*v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Dot)
{
	Vector4 a(1,2,3,4);
	Vector4 b(-5,-2,4,5);
	float e=23;
	CHECK(Dot(a,b)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Mag)
{
	Vector4 v(0,3,4,0);
	float e=5;
	CHECK(Mag(v)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector4,Normalize)
{
	Vector4 v(0,3,4,0);
	CHECK(Normalize(v)==Vector4(0, 3.0/5, 4.0/5, 0));
	CASE_SUCCESS;
}

#endif