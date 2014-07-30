#ifndef MYMATH_H
#define MYMATH_H

class Vector3
{
private:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float f[3];
	};
public:
	Vector3(float f3[]);
	Vector3(float x,float y,float z);
	float operator[](int i) const;
	friend Vector3 operator+(Vector3 a,Vector3 b);
	friend Vector3 operator-(Vector3 a,Vector3 b);
	friend Vector3 operator*(Vector3 a,float k);
	friend Vector3 operator*(float k,Vector3 a);
	friend Vector3 operator/(Vector3 a,float k);
	friend bool    operator==(Vector3 a,Vector3 b);
	friend bool    operator!=(Vector3 a,Vector3 b);
	friend Vector3 operator+=(Vector3 a,Vector3 b);
	friend Vector3 operator-=(Vector3 a,Vector3 b);
	friend float   Dot(Vector3 a,Vector3 b);
	friend float   Norm(Vector3 a);
	friend Vector3 Normalize(Vector3 a);
};

class Vector4
{
private:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float f[4];
	};
public:
	Vector4(float f4[]);
	Vector4(float x,float y,float z,float w);
	friend Vector4 operator+(Vector4 a,Vector4 b);
	friend Vector4 operator-(Vector4 a,Vector4 b);
	friend Vector4 operator*(Vector4 a,float k);
	friend Vector4 operator*(float k,Vector4 a);
	friend Vector4 operator/(Vector4 a,float k);
	friend bool    operator==(Vector4 a,Vector4 b);
	friend bool    operator!=(Vector4 a,Vector4 b);
	friend Vector4 operator+=(Vector4 a,Vector4 b);
	friend Vector4 operator-=(Vector4 a,Vector4 b);
	friend float   Dot(Vector4 a,Vector4 b);
	friend float   Norm(Vector4 a);
	friend Vector4 Normalize(Vector4 a);
};

class Matrix3
{
private:
	union
	{
		struct
		{
			float m11,m12,m13;
			float m21,m22,m23;
			float m31,m32,m33;
		};
		float f[9];
		float m[3][3];
	};
public:
	Matrix3();
	Matrix3(float f9[]);
	Matrix3(float m11,float m12,float m13,float m21,float m22,float m23,float m31,float m32,float m33);
	float operator()(int i) { return f[i]; }
	float operator()(int i,int j) { return m[i-1][j-1];}
	friend Matrix3 operator+(Matrix3 a,Matrix3 b);
	friend Matrix3 operator-(Matrix3 a,Matrix3 b);
	friend Matrix3 operator*(Matrix3 a,Matrix3 b);
	friend Matrix3 operator*(Matrix3 a,float k);
	friend Matrix3 operator*(float k,Matrix3 a);
	friend Matrix3 operator/(Matrix3 a,float k);
	friend bool    operator==(Matrix3 a,Matrix3 b);
	friend bool    operator!=(Matrix3 a,Matrix3 b);
	friend Matrix3 operator+=(Matrix3 a,Matrix3 b);
	friend Matrix3 operator-=(Matrix3 a,Matrix3 b);
	friend Matrix3 Transpose(Matrix3 m);
};

class Matrix4
{
private:
	union
	{
		struct
		{
			float m11,m12,m13,m14;
			float m21,m22,m23,m24;
			float m31,m32,m33,m34;
			float m41,m42,m43,m44;
		};
		float f[16];
		float m[4][4];
	};
public:
	Matrix4();
	Matrix4(float f[]);
	Matrix4(float m11,float m12,float m13,float m14,float m21,float m22,float m23,float m24,float m31,float m32,float m33,float m34,float m41,float m42,float m43,float m44);
	float operator()(int i) { return f[i]; }
	float operator()(int i,int j) {return m[i-1][j-1]; }
	operator float*();
	friend Matrix4 operator+(Matrix4 a,Matrix4 b);
	friend Matrix4 operator-(Matrix4 a,Matrix4 b);
	friend Matrix4 operator*(Matrix4 a,Matrix4 b);
	friend Matrix4 operator*(Matrix4 a,float k);
	friend Matrix4 operator*(float k,Matrix4 a);
	friend Matrix4 operator/(Matrix4 a,float k);
	friend bool    operator==(Matrix4 a,Matrix4 b);
	friend bool    operator!=(Matrix4 a,Matrix4 b);
	friend Matrix4 operator+=(Matrix4 a,Matrix4 b);
	friend Matrix4 operator-=(Matrix4 a,Matrix4 b);
	friend Matrix4 Transpose(Matrix4 m);
	void print();
};



const float PI = 3.1415926;

float Det(Matrix4 m);

Matrix4 Identity();
Matrix4 Translate(const Vector3& v);
Matrix4 Rotate(const Vector3& v, float angle);
Matrix4 Perspective(float fovy, float aspect, float nearZ, float farZ);
Matrix4 Ortho(float left, float right, float bottom, float top, float near, float far);
Matrix4 Transpose(Matrix4 m);
Matrix4 LookAt(const Vector3 eye,const Vector3 target,const Vector3 up);



#endif