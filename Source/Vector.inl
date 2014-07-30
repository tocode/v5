#ifndef VECTOR_INL
#define VECTOR_INL

#include <assert.h>
#include <math.h>
#include <string.h>

template<class T, int D>
Vector<T,D>::Vector()
{
	T t[D]={0};
	memcpy(data,t,D*sizeof(T));
};

template<class T, int D>
Vector<T,D>::Vector(const T* a)
{
	memcpy(data,a,D*sizeof(T));
}

template<class T, int D>
Vector<T,D>::Vector(const Vector<T,D>& v)
{
	memcpy(data,v.data,D*sizeof(T));
}

template<class T, int D>
Vector<T,D>& Vector<T,D>::operator=(const Vector<T,D>& v)
{
	if (this!=&v)
	{
		memcpy(data,v.data,D*sizeof(T));
	}
	return *this;
}

template<class T, int D>
T Vector<T,D>::operator[](int i) const
{
	assert(i>=0);
	assert(i<D);
	return data[i];
}

template<class T, int D>
T& Vector<T,D>::operator[](int i)
{
	assert(i>=0);
	assert(i<D);
	return data[i];
};

template<class T, int D>
T Vector<T,D>::operator()(int i) const
{
	assert(i>0);
	assert(i<=D);
	return data[i-1];
}

template<class T, int D>
T& Vector<T,D>::operator()(int i)
{
	assert(i>0);
	assert(i<=D);
	return data[i-1];
}

template<class T, int D>
bool Vector<T,D>::operator==(const Vector<T,D>& v) const
{
	return memcmp(data,v.data,D*sizeof(T))==0;
}

template<class T, int D>
bool Vector<T,D>::operator!=(const Vector<T,D>& v) const
{
	return memcmp(data,v.data,D*sizeof(T))!=0;
}

template<class T, int D>
Vector<T,D> Vector<T,D>::operator+(const Vector<T,D>& v) const
{
	Vector<T,D> result;
	for (int i=0; i<D; i++)
		result.data[i]=data[i]+v.data[i];
	return result;
}

template<class T, int D>
Vector<T,D> Vector<T,D>::operator-(const Vector<T,D>& v) const
{
	Vector<T,D> result;
	for (int i=0; i<D; i++)
		result.data[i]=data[i]-v.data[i];
	return result;
};

template<class T, int D>
Vector<T,D> Vector<T,D>::operator-() const
{
	Vector<T,D> r;
	for (int i=0; i<D; i++)
		r.data[i]=-data[i];
	return r;
}

template<class T, int D>
Vector<T,D> Vector<T,D>::operator*(T k) const
{
	Vector<T,D> result;
	for (int i=0; i<D; i++)
		result[i]=data[i]*k;
	return result;
}
template<class T, int D>
Vector<T,D> Vector<T,D>::operator/(T k) const
{
	Vector<T,D> result;
	T u=1/k;
	for (int i=0; i<D; i++)
		result[i] = data[i]*u;
	return result;
}

template<class T, int D>
Vector<T,D>& Vector<T,D>::operator+=(const Vector<T,D>& v)
{
	for (int i=0; i<D; i++)
		data[i]+=v.data[i];
	return *this;
}

template<class T, int D>
Vector<T,D>& Vector<T,D>::operator-=(const Vector<T,D>& v)
{
	for (int i=0; i<D; i++)
		data[i]-=v.data[i];
	return *this;
}

template<class T, int D>
Vector<T,D>& Vector<T,D>::operator*=(T k)
{
	for (int i=0; i<D; i++)
		data[i]*=k;
	return *this;
};

template<class T, int D>
Vector<T,D>& Vector<T,D>::operator/=(T k)
{
	T u=1/k;
	for (int i=0; i<D; i++)
		data[i] *= u;
	return *this;
}



//********** non member function **********************

template<class T,int D>
Vector<T,D> operator*(T k, const Vector<T,D>& v)
{
	return v*k;
}

template<class T, int D>
T Dot(const Vector<T,D>& a, const Vector<T,D>& b)
{
	T r=0;
	for (int i=0; i<D; i++)
		r+=a[i]*b[i];
	return r;
}

template<class T, int D>
T Mag(const Vector<T,D>& v)
{
	return sqrt(Dot(v,v));
}

template<class T, int D>
Vector<T,D> Normalize(const Vector<T,D>& v)
{
	return v/Mag(v);
}

#endif