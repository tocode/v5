#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#define PI 3.1415926

#include "Vector.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"

Vector3 operator*(const Matrix3& m, const Vector3& v);
Vector4 operator*(const Matrix4& m, const Vector4& v);


Matrix4 Identity();
Matrix4 Translate(const Vector3& v);
Matrix4 Scale(const Vector3& v);
Matrix4 Rotate(const Vector3& v, float angle);
Matrix4 Perspective(float fovy, float aspect, float nearZ, float farZ);
Matrix4 Ortho(float left, float right, float bottom, float top, float near, float far);
Matrix4 LookAt(const Vector3 eye,const Vector3 target,const Vector3 up);


#endif