#ifndef TESTVECTOR2_H
#define TESTVECTOR2_H

#include "TestFrame.h"
#include "Vector2.h"

DEF_CASE2(Vector2,Operator_float_star)
{
	Vector2 v(1,2);
	float* f = v;
	float r[] = {1,2};
	CHECK(r[0]==f[0]);
	CHECK(r[1]==f[1]);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,construction_default)
{
	Vector2 v;
	CHECK(v.X==0);
	CHECK(v.Y==0);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,construction_array)
{
	float a[]={0,1};
	Vector2 v(a);
	CHECK(v.X==0);
	CHECK(v.Y==1);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,construction_copy)
{
	Vector2 v(1,2);
	Vector2 e(1,2);
	Vector2 r(v);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,construction_from_Vector2)
{
	float a[]={0,1};
	Vector2 v(a);
	Vector2 v3(v);
	Vector2 e(0,1);
	CHECK(v3==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,assign_01)
{
	Vector2 v(1,2);
	Vector2 e(1,2);
	Vector2 r;
	r=v;
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,assign_02)
{
	Vector2 r;
	Vector2 e(5,7);
	r=Vector2(1,2)+Vector2(4,5);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_index_const)
{
	Vector2 v(1,2);
	CHECK(v[0]==1);
	CHECK(v[1]==2);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_index)
{
	Vector2 v;
	Vector2 e(1,2);
	v[0]=1;
	v[1]=2;
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_math_index_const)
{
	Vector2 v(1,2);
	CHECK(v(1)==1);
	CHECK(v(2)==2);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_math_index)
{
	Vector2 v;
	Vector2 e(1,2);
	v(1)=1;
	v(2)=2;
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_eq)
{
	Vector2 a(1,2);
	Vector2 b(1,2);
	CHECK(a==b);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_ne)
{
	Vector2 a(1,2);
	Vector2 b(0,1);
	CHECK(a!=b);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_add)
{
	Vector2 a(1,2);
	Vector2 b(4,5);
	Vector2 e(5,7);
	CHECK(a+b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_sub)
{
	Vector2 a(9,8);
	Vector2 b(1,2);
	Vector2 e(8,6);
	CHECK(a-b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_negative)
{
	Vector2 a(1,2);
	Vector2 e(-1,-2);
	CHECK(-a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_mul_Vk)
{
	Vector2 v(1,2);
	float k=3;
	Vector2 e(3,6);
	CHECK(v*k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_div)
{
	Vector2 v(3,6);
	float k=3;
	Vector2 e(1,2);
	CHECK(v/k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_reflexive_add)
{
	Vector2 v(1,2);
	v+=Vector2(5,6);
	Vector2 e(6,8);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_reflexive_sub)
{
	Vector2 v(5,6);
	v-=Vector2(1,-9);
	Vector2 e(4,15);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_reflexive_mul)
{
	Vector2 v(1,2);
	v*=3;
	Vector2 e(3,6);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Operator_reflexive_div)
{
	Vector2 v(3,6);
	v/=3;
	Vector2 e(1,2);
	CHECK(v==e);
	CASE_SUCCESS;
}


// ***** NON MEMBER FUNCTION *****

DEF_CASE2(Vector2,Operator_mul_kV)
{
	Vector2 v(1,2);
	float k=3;
	Vector2 e(3,6);
	CHECK(k*v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Dot)
{
	Vector2 a(1,2);
	Vector2 b(-5,-2);
	float e=-9;
	CHECK(Dot(a,b)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Mag)
{
	Vector2 v(3,4);
	float e=5;
	CHECK(Mag(v)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector2,Normalize)
{
	Vector2 v(3,4);
	CHECK(Normalize(v)==Vector2(3.0/5, 4.0/5));
	CASE_SUCCESS;
}

#endif