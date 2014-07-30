#ifndef CAMERA_H
#define CAMERA_H

#include "GL.h"
#include "Mathematics.h"

class Camera
{
public:
	Camera(Vector3 position,Vector3 look,Vector3 up,float fovy,float aspect,float nearZ=1,float farZ=1000)
	{
		this->position = position;
		this->look = look;
		//this->right = CrossProduct(look,up);
		this->up = up;
		this->fovy = fovy;
		this->aspect = aspect;
		this->nearZ = nearZ;
		this->farZ = farZ;
	}
	Matrix4 ViewMatrix()
	{
		return LookAt(position,position+look,up);
	}
	Matrix4 ProjectionMatrix()
	{
		return Perspective(fovy, aspect, nearZ, farZ);
	}
	Matrix4 VPMatrix()
	{
		return ProjectionMatrix()*ViewMatrix();
	}
	void Pitch(float angle)
	{
		right = CrossProduct(look,up);
		look = (Rotate(right,angle)*Vector4(look,1)).XYZ();
	}
	void Yaw(float angle)
	{
		look = (Rotate(up,angle)*Vector4(look,1)).XYZ();
		//right = (Rotate(up,angle)*Vector4(look,1)).XYZ();
	}
	void Roll(float angle)
	{
		up = (Rotate(look,angle)*Vector4(up,1)).XYZ();
	}
	void Forward(float distance)
	{
		position += distance * look;
	}
	void Backward(float distance)
	{
		position -= distance * look;
	}
	void StrafeLeft(float distance)
	{
		right = CrossProduct(look,up);
		position -= distance * right;
	}
	void StrafeRight(float distance)
	{
		right = CrossProduct(look,up);
		position += distance* right;
	}
	Vector3 Position() const
	{
		return position;
	}
	void SetPosition(const Vector3& position)
	{
		this->position = position;
	}
	Vector3 Look() const
	{
		return look;
	}
	void SetLook(const Vector3& look)
	{
		this->look = look;
	}
private:
	Vector3 position;
	Vector3 look;
	Vector3 right;
	Vector3 up;
	float fovy;
	float aspect;
	float nearZ;
	float farZ;
};
DECLARE_POINTER_OF(Camera);

CameraPtr MakeCamera(Vector3 position,Vector3 look,Vector3 up,float fovy,float aspect,float nearZ=1,float farZ=1000)
{
	return CameraPtr(new Camera(position,look,up,fovy,aspect,nearZ,farZ));
}

#endif