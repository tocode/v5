#ifndef VECTOR_H
#define VECTOR_H

template <class T, int D>
class Vector
{
public:
						Vector();
	explicit			Vector(const T* a);
						Vector(const Vector& v);

	Vector&				operator=(const Vector& v);
	T					operator[](int i) const;
	T&					operator[](int i);
	T					operator()(int i) const;
	T&					operator()(int i);

	bool				operator==(const Vector& v) const;
	bool				operator!=(const Vector& v) const;

	Vector				operator+(const Vector& v) const;
	Vector				operator-(const Vector& v) const;
	Vector				operator-() const;
	Vector				operator*(T k) const;
	Vector				operator/(T k) const;
	Vector&				operator+=(const Vector& v);
	Vector&				operator-=(const Vector& v);
	Vector&				operator*=(T k);
	Vector&				operator/=(T k);

	int					Dimention() { return D; }
	void*				DataPointer() {	return data; }

private:
	T data[D];
};

// k*V
template<class T, int D>
Vector<T,D> operator*(T k, const Vector<T,D>& v);

// dot - A.B
template<class T, int D>
T Dot(const Vector<T,D>& a, const Vector<T,D>& b);

// mag
template<class T, int D>
T Mag(const Vector<T,D>& v);

// normalize
template<class T, int D>
Vector<T,D> Normalize(const Vector<T,D>& v);



#include "Vector.inl"

#endif