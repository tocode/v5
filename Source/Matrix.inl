#ifndef MATRIX_INL
#define MATRIX_INL

#include <assert.h>
#include <string>

template<class T, int M, int N>
Matrix<T,M,N>::Matrix()
{
	T t[M*N]={0};
	memcpy(data2,t,M*N*sizeof(T));
}

template<class T, int M, int N>
Matrix<T,M,N>::Matrix(const T* a)
{
	memcpy(data2,a,M*N*sizeof(T));
}

template<class T, int M, int N>
Matrix<T,M,N>::Matrix(const Matrix& m)
{
	memcpy(data2,m.data2,M*N*sizeof(T));
}

template<class T, int M, int N>
Matrix<T,M,N>& Matrix<T,M,N>::operator=(const Matrix& m)
{
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
		data2[i][j]=m.data2[i][j];
	return *this;
}

template<class T, int M, int N>
T Matrix<T,M,N>::operator()(int i, int j) const
{
	assert(i>0);
	assert(i<=M);
	assert(j>0);
	assert(j<=N);
	return data2[i-1][j-1];
}

template<class T, int M, int N>
T& Matrix<T,M,N>::operator()(int i, int j)
{
	assert(i>0);
	assert(i<=M);
	assert(j>0);
	assert(j<=N);
	return data2[i-1][j-1];
}

template<class T, int M, int N>
bool Matrix<T,M,N>::operator==(const Matrix& m) const
{
	return memcmp(data2,m.data2,M*N*sizeof(T))==0;
}

template<class T, int M, int N>
bool Matrix<T,M,N>::operator!=(const Matrix& m) const
{
	return memcmp(data2,m.data2,M*N*sizeof(T))!=0;
}

template<class T, int M, int N>
Matrix<T,M,N> Matrix<T,M,N>::operator+(const Matrix& m) const
{
	Matrix<T,M,N> result;
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			result.data2[i][j]=data2[i][j]+m.data2[i][j];
	return result;
}

template<class T, int M, int N>
Matrix<T,M,N> Matrix<T,M,N>::operator-(const Matrix& m) const
{
	Matrix<T,M,N> result;
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			result.data2[i][j]=data2[i][j]-m.data2[i][j];
	return result;
}

template<class T, int M, int N>
Matrix<T,M,N> Matrix<T,M,N>::operator-() const
{
	Matrix<T,M,N> result;
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			result.data2[i][j]=-data2[i][j];
	return result;
}

template<class T, int M, int N>
Matrix<T,M,N> Matrix<T,M,N>::operator*(const T k) const
{
	Matrix<T,M,N> r;
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			r.data2[i][j]=k*data2[i][j];
	return r;
}

template<class T, int M, int N>
Matrix<T,M,N> Matrix<T,M,N>::operator/(const T k) const
{
	Matrix<T,M,N> r;
	T u=1/k;
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			r.data2[i][j]=data2[i][j]*u;
	return r;
}

template<class T, int M, int N>
Matrix<T,M,N>& Matrix<T,M,N>::operator+=(const Matrix& m)
{
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			data2[i][j]+=m.data2[i][j];
	return *this;
}

template<class T, int M, int N>
Matrix<T,M,N>& Matrix<T,M,N>::operator-=(const Matrix& m)
{
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			data2[i][j]-=m.data2[i][j];
	return *this;
}

template<class T, int M, int N>
Matrix<T,M,N>& Matrix<T,M,N>::operator*=(const T k)
{
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			data2[i][j]*=k;
	return *this;
}

template<class T, int M, int N>
Matrix<T,M,N>& Matrix<T,M,N>::operator/=(const T k)
{
	T u=1/k;
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			data2[i][j]*=u;
	return *this;
}


// ***** non member function *****

template<class T, int M, int N>
Matrix<T,M,N> operator*(const T k, const Matrix<T,M,N>& m)
{
	return m*k;
}

template<class T, int M, int N, int R>
Matrix<T,M,R> operator*(const Matrix<T,M,N>& a, const Matrix<T,N,R>& b)
{
	Matrix<T,M,R> r;
	for (int i=1; i<=M; i++)
		for (int j=1; j<=R; j++)
		{
			double r_i_j=r(i,j);
			for (int k=1; k<=N; k++)
				r_i_j+=(double)a(i,k)*(double)b(k,j);
			r(i,j) = r_i_j;
		}
	return r;
}

// M^T
template<class T, int M, int N>
Matrix<T,M,N> Transpose(const Matrix<T,M,N>& m)
{
	Matrix<T,M,N> r;
	for (int i=1; i<=M; i++)
		for (int j=1; j<=N; j++)
			r(i,j)=m(j,i);
	return r;
}

template<class T,int M>
T Det(const Matrix<T,M,M>& m)
{ 
	T s=0;
	int i=1;
	for (int j=1; j<=M; j++)
	{
		s+=m(i,j)*AlgebraCofactor(m,i,j);
	}
	return s;
}
template<class T>
T Det(const Matrix<T,1,1>& m)
{
	return m(1,1);
}

template<class T, int M>
Matrix<T,M-1,M-1> Cofactor(const Matrix<T,M,M>& m, int u, int v)
{
	Matrix<T,M-1,M-1> mm;
	int ii=1;
	for (int i=1; i<=M; i++)
		if (i!=u)
		{		
			int jj=1;
			for (int j=1; j<=M; j++)
				if (j!=v)
					mm(ii,jj++)=m(i,j);
			ii++;
		}
		return mm; 
}

template<class T, int M>
T AlgebraCofactor(const Matrix<T,M,M>& m, int u, int v)
{
	T k=(u+v)%2==0?1:-1;
	return k*Det(Cofactor(m,u,v));
}

template<class T, int M, int N>
Matrix<T,M,N> Adj(const Matrix<T,M,N>& m)
{
	Matrix<T,M,N> r;
	for (int i=1; i<=M; i++)
		for (int j=1; j<=N; j++)
			r(i,j)=AlgebraCofactor(m,j,i);
	return r;
}

template<class T, int M, int N>
Matrix<T,M,N> Inverse(const Matrix<T,M,N>& m)
{
	T DetOfM=Det(m);
	assert(DetOfM);
	return Adj(m)/DetOfM;
}

#endif