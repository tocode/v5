#ifndef TESTVECTOR_H
#define TESTVECTOR_H

#include "TestFrame.h"
#include "Vector.h"

DEF_CASE2(Vector,Vector)
{
	Vector<float,5> v;
	CASE_SUCCESS;
}

DEF_CASE2(Vector,Vector_array)
{
	float a[]={1,2,3};
	Vector<float,3> vec(a);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Vector_copy)
{
	float a[]={1,2,3};
	Vector<float,3> vec(a);
	Vector<float,3> vec_new(vec);
	CASE_SUCCESS;
}

DEF_CASE2(Vector,Assign)
{
	float a[]={1,2,3};
	float b[]={4,5,6};
	float e[]={4,5,6};
	Vector<float,3> va(a);
	Vector<float,3> vb(b);
	Vector<float,3> ve(e);
	va=vb;
	CHECK(va==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_index_const)
{
	float a[]={1,2,3};
	Vector<float,3> v(a);
	CHECK(v[0]==1);
	CHECK(1==v[0]);
	CHECK(v[1]==2);
	CHECK(2==v[1]);
	CHECK(v[2]==3);
	CHECK(3==v[2]);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_index)
{
	float a[]={1,2,3};
	Vector<float,3> v(a);
	v[0]=9;
	v[1]=8;
	v[2]=7;
	CHECK(v[0]==9);
	CHECK(v[1]==8);
	CHECK(v[2]==7);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_math_index_const)
{
	float a[]={1,2,3};
	Vector<float,3> v(a);
	CHECK(v(1)==1);
	CHECK(1==v(1));
	CHECK(v(2)==2);
	CHECK(2==v(2));
	CHECK(v(3)==3);
	CHECK(3==v(3));
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_math_index)
{
	float a[]={1,2,3};
	Vector<float,3> v(a);
	v(1)=9;
	v(2)=8;
	v(3)=7;
	CHECK(v(1)==9);
	CHECK(v(2)==8);
	CHECK(v(3)==7);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_eq)
{
	float a[]={1,2,3};
	float b[]={1,2,3};
	float c[]={4,5,6};
	Vector<float,3> va(a);
	Vector<float,3> vb(b);
	Vector<float,3> vc(c);
	CHECK(va==vb);
	CHECK(vb==va);
	CHECKNOT(va==vc);
	CHECKNOT(vc==va);
	CHECKNOT(vb==vc);
	CHECKNOT(vc==vb);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_ne)
{
	float a[]={1,2,3};
	float b[]={1,2,3};
	float c[]={4,5,6};
	Vector<float,3> va(a);
	Vector<float,3> vb(b);
	Vector<float,3> vc(c);
	CHECKNOT(va!=vb);
	CHECKNOT(vb!=va);
	CHECK(va!=vc);
	CHECK(0);
	CHECK(vc!=va);
	CHECK(vb!=vc);
	CHECK(vc!=vb);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_add)
{
	float a[]={1,2,3};
	float b[]={9,8,7};
	float e[]={10,10,10};
	float r[]={0};
	Vector<float,3> va(a);
	Vector<float,3> vb(b);
	Vector<float,3> ve(e);
	Vector<float,3> vr(r);
	vr=va+vb;
	CHECK(vr==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_sub)
{
	float a[]={1,2,3};
	float b[]={9,8,7};
	float e[]={-8,-6,-4};
	float r[]={0};
	Vector<float,3> va(a);
	Vector<float,3> vb(b);
	Vector<float,3> ve(e);
	Vector<float,3> vr(r);
	vr=va-vb;
	CHECK(vr==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_negative)
{
	float a[]={0,1,2};
	float e[3];
	for (int i=0; i<3; i++) e[i]=-a[i];
	Vector<float,3> va(a);
	Vector<float,3> ve(e);
	Vector<float,3> vr(-va);
	CHECK(vr==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_mul_Vk)
{
	float a[]={0,1,2,3};
	float e[]={0,5,10,15};
	Vector<float,4> va(a);
	Vector<float,4> ve(e);
	Vector<float,4> vr;
	float k=5;
	vr=va*k;
	CHECK(vr==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_div)
{
	float a[]={0,5,10,15,};
	float e[]={0,1,2,3};
	Vector<float,4> va(a);
	Vector<float,4> ve(e);
	Vector<float,4> vr;
	float k=5;
	vr=va/k;
	CHECK(vr==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_add_assign)
{
	float a[]={1,2,3};
	float b[]={9,8,7};
	float e[]={10,10,10};
	Vector<float,3> va(a);
	Vector<float,3> vb(b);
	Vector<float,3> ve(e);
	va+=vb;
	CHECK(va==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_sub_assign)
{
	float a[]={1,2,3};
	float b[]={9,8,7};
	float e[]={-8,-6,-4};
	Vector<float,3> va(a);
	Vector<float,3> vb(b);
	Vector<float,3> ve(e);
	va-=vb;
	CHECK(va==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_mul_assign)
{
	float a[]={0,1,2,3,};
	float e[]={0,5,10,15};
	Vector<float,4> va(a);
	Vector<float,4> ve(e);
	float k=5;
	va*=k;
	CHECK(va==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_div_assign)
{
	float a[]={0,5,10,15,};
	float e[]={0,1,2,3};
	Vector<float,4> va(a);
	Vector<float,4> ve(e);
	float k=5;
	va/=k;
	CHECK(va==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Dimention)
{
	float a[]={1,2,3,4,5};
	Vector<float,5> va(a);
	CHECK(va.Dimention()==5);
	CASE_SUCCESS;
}

//********** non member function **********

DEF_CASE2(Vector,Operator_mul_kV)
{
	float a[]={0,1,2,3,};
	float e[]={0,5,10,15};
	Vector<float,4> va(a);
	Vector<float,4> ve(e);
	Vector<float,4> vr;
	float k=5;
	vr=k*va;
	CHECK(vr==ve);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Operator_dot)
{
	float a[]={0,1,2,3};
	float b[]={4,5,6,7};
	Vector<float,4> va(a);
	Vector<float,4> vb(b);
	CHECK(Dot(va,vb)==38);
	CASE_SUCCESS;
}
DEF_CASE2(Vector,Mag)
{
	float a[]={0,3,0,4};
	Vector<float,4> v(a);
	CHECK(Mag(v)==5);
	CASE_SUCCESS;
}

DEF_CASE2(Vector,Normalize)
{
	float a[]={0,0,3,4};
	float e[]={0,0,3.0/5,4.0/5};
	Vector<float,4> va(a);
	Vector<float,4> ve(e);
	CHECK(Normalize(va)==ve);
	CASE_SUCCESS;
}

#endif