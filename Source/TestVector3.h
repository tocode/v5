#ifndef TESTVECTOR3_H
#define TESTVECTOR3_H

#include "TestFrame.h"
#include "Vector3.h"

DEF_CASE2(Vector3,Operator_float_star)
{
	Vector3 v(1,2,3);
	float* f = v;
	float r[] = {1,2,3};
	CHECK(r[0]==f[0]);
	CHECK(r[1]==f[1]);
	CHECK(r[2]==f[2]);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,construction_default)
{
	Vector3 v;
	CHECK(v.X==0);
	CHECK(v.Y==0);
	CHECK(v.Z==0);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,construction_array)
{
	float a[]={0,1,2};
	Vector3 v(a);
	CHECK(v.X==0);
	CHECK(v.Y==1);
	CHECK(v.Z==2);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,construction_copy)
{
	Vector3 v(1,2,3);
	Vector3 e(1,2,3);
	Vector3 r(v);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,construction_from_Vector3)
{
	float a[]={0,1,2};
	Vector3 v(a);
	Vector3 v3(v);
	Vector3 e(0,1,2);
	CHECK(v3==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,assign_01)
{
	Vector3 v(1,2,3);
	Vector3 e(1,2,3);
	Vector3 r;
	r=v;
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,assign_02)
{
	Vector3 r;
	Vector3 e(5,7,9);
	r=Vector3(1,2,3)+Vector3(4,5,6);
	CHECK(r==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_index_const)
{
	Vector3 v(1,2,3);
	CHECK(v[0]==1);
	CHECK(v[1]==2);
	CHECK(v[2]==3);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_index)
{
	Vector3 v;
	Vector3 e(1,2,3);
	v[0]=1;
	v[1]=2;
	v[2]=3;
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_math_index_const)
{
	Vector3 v(1,2,3);
	CHECK(v(1)==1);
	CHECK(v(2)==2);
	CHECK(v(3)==3);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_math_index)
{
	Vector3 v;
	Vector3 e(1,2,3);
	v(1)=1;
	v(2)=2;
	v(3)=3;
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_eq)
{
	Vector3 a(1,2,3);
	Vector3 b(1,2,3);
	CHECK(a==b);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_ne)
{
	Vector3 a(1,2,3);
	Vector3 b(0,1,2);
	CHECK(a!=b);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_add)
{
	Vector3 a(1,2,3);
	Vector3 b(4,5,6);
	Vector3 e(5,7,9);
	CHECK(a+b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_sub)
{
	Vector3 a(9,8,7);
	Vector3 b(1,2,3);
	Vector3 e(8,6,4);
	CHECK(a-b==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_negative)
{
	Vector3 a(1,2,3);
	Vector3 e(-1,-2,-3);
	CHECK(-a==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_mul_Vk)
{
	Vector3 v(1,2,3);
	float k=3;
	Vector3 e(3,6,9);
	CHECK(v*k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_div)
{
	Vector3 v(3,6,9);
	float k=3;
	Vector3 e(1,2,3);
	CHECK(v/k==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_reflexive_add)
{
	Vector3 v(1,2,3);
	v+=Vector3(5,6,-7);
	Vector3 e(6,8,-4);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_reflexive_sub)
{
	Vector3 v(5,6,7);
	v-=Vector3(1,-9,2);
	Vector3 e(4,15,5);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_reflexive_mul)
{
	Vector3 v(1,2,3);
	v*=3;
	Vector3 e(3,6,9);
	CHECK(v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Operator_reflexive_div)
{
	Vector3 v(3,6,9);
	v/=3;
	Vector3 e(1,2,3);
	CHECK(v==e);
	CASE_SUCCESS;
}


// ***** NON MEMBER FUNCTION *****

DEF_CASE2(Vector3,Operator_mul_kV)
{
	Vector3 v(1,2,3);
	float k=3;
	Vector3 e(3,6,9);
	CHECK(k*v==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Dot)
{
	Vector3 a(1,2,3);
	Vector3 b(-5,-2,4);
	float e=3;
	CHECK(Dot(a,b)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Mag)
{
	Vector3 v(0,3,4);
	float e=5;
	CHECK(Mag(v)==e);
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,Normalize)
{
	Vector3 v(0,3,4);
	CHECK(Normalize(v)==Vector3(0, 3.0/5, 4.0/5));
	CASE_SUCCESS;
}
DEF_CASE2(Vector3,CrossProduct)
{
	Vector3 r = CrossProduct(Vector3(1,3,4),Vector3(2,-5,8));
	Vector3 e(44,0,-11);
	CHECK( r==e );
	CASE_SUCCESS;
}
#endif