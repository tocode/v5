#ifndef MATRIX_H
#define MATRIX_H


template<class T, int M, int N>
class Matrix
{
public:
						Matrix();
	explicit			Matrix(const T* a);
						Matrix(const Matrix& m);

	Matrix&				operator=(const Matrix& m);
	T					operator()(int i, int j) const;
	T&					operator()(int i, int j);
	
	bool				operator==(const Matrix& m) const;
	bool				operator!=(const Matrix& m) const;

	Matrix				operator+(const Matrix& m) const;
	Matrix				operator-(const Matrix& m) const;
	Matrix				operator-() const;
	Matrix				operator*(const T k) const;
	Matrix				operator/(const T k) const;
	Matrix&				operator+=(const Matrix& m);
	Matrix&				operator-=(const Matrix& m);
	Matrix&				operator*=(const T k);
	Matrix&				operator/=(const T k);

	int					RowNum() const {return M;}
	int					ColumnNum() const {return N;}
	void*				DataPointer() {return data1;}

private:
	union
	{
		T data1[M*N];
		T data2[M][N];
	};
};

// k*M
template<class T, int M, int N>
Matrix<T,M,N> operator*(const T k, const Matrix<T,M,N>& m);

// A*B
template<class T,int M,int N,int R>
Matrix<T,M,R> operator*(const Matrix<T,M,N>& a, const Matrix<T,N,R>& b);

// M^T
template<class T, int M, int N>
Matrix<T,M,N> Transpose(const Matrix<T,M,N>& m);

// |M|
template<class T,int M>
T Det(const Matrix<T,M,M>& m);

// |M| (1*1)
template<class T>
T Det(const Matrix<T,1,1>& m);

// cofactor
template<class T, int M>
Matrix<T,M-1,M-1> Cofactor(const Matrix<T,M,M>& m, int u, int v);

// algebra cofactor
template<class T, int M>
T AlgebraCofactor(const Matrix<T,M,M>& m, int u, int v);

// adj
template<class T, int M, int N>
Matrix<T,M,N> Adj(const Matrix<T,M,N>& m);

// M^-1
template<class T, int M, int N>
Matrix<T,M,N> Inverse(const Matrix<T,M,N>& m);


#include "Matrix.inl"

#endif