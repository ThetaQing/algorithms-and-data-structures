#ifndef __ARRAYANDMATRIX_H__
#define __ARRAYANDMATRIX_H__

#include <iostream>
#include <sstream>
#include "myExceptions.h"
using namespace std;
/*****************�ļ�����********************
* �ļ�����arrayAndMatrix.h
* �ļ����ܣ������ݽṹ�������� ���������


**/

#ifndef __MATRIX_
#define __MATRIX_
/********************����˵��*******************
=================================================

* �����ţ�7-2  P153
* �����ܣ�������matrix��������ʵ��
* ��ĳ�Ա������
			1�����캯����Ĭ�Ϲ��캯���͸��ƹ��캯������
			2������������
			3�����������ĺ�����
			4�����������ĺ�����
			5�����������=��+��-��������*
			6��ת������


=================================================
**/

/****************����˵��***********
* �����ܣ�matrix�������


*/
template<class T>
class matrix
{
	friend ostream& operator<< (ostream&, const matrix<T>&);
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>&);
	~matrix() { delete[] element; }
	int rows() const { return theRows; };  // ���������ĺ���
	int columns() const { return theColumns; }  // ���������ĺ���
	T& operator() (int i, int j) const;
	matrix<T>& operator = (const matrix<T>&);
	matrix<T> operator +() const;  // ��Ŀ�����+
	matrix<T> operator +(const matrix<T>&) const;
	matrix<T> operator -() const;  // ��Ŀ�����-
	matrix<T> operator -(const matrix<T>&) const;
	matrix<T>& operator +=(const T&);
	matrix<T> operator *(const matrix<T>&) const;

	// ת������
	matrix<T> trans();


private:
	int theRows;  // ���������
	int theColumns;  // ���������
	T* element;  // ����element
};

/*****************����˵��*************************
* ��������matrix(int theRows, int theColumns)
* �����������½����������������
* ��������ֵ��һ��theRows*theColumns�ľ���
* �������ܣ������캯��
* ע�⣺���캯��������������������������0�ľ���Ҳ����0*0�ľ���

**/
template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
	// ������������������Ч��
	if (theRows < 0 || theColumns < 0)
		throw "Rows and columns must be >= 0";
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
		throw "Either both or neither rows and columns should be zero";
	// ��������
	this->theColumns = theColumns;
	this->theRows = theRows;
	element = new T[theRows * theColumns];
}
/*****************����˵��*************************
* ��������matrix(const matrix<T>& m)
* ����������ԭ����
* ��������ֵ��һ����ԭ����һ���ľ���
* �������ܣ�����ĸ��ƹ��캯��
* ע�⣺���캯��������������������������0�ľ���Ҳ����0*0�ľ���

**/
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
	// ��������
	theRows = m.theRows;
	theColumns = m.theColumns;
	element = new T[theRows * theColumns];

	// ����m��ÿ��Ԫ��
	copy(m.element, m.element + theRows * theColumns, element);  // ��һ����������ʼ���Ƶ�Ԫ�ص�ַ���ڶ������������һ�����Ƶ�Ԫ�ص�ַ��������������Ŀ�ĵص���ʼ��ַ
}
/************����˵��*****************
* ��������matrix<T>& operator=(const matrix<T>& m)
* ����������һ������
* ��������ֵ������
* �������ܣ����ظ�ֵ�����=

**/
template <class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	if (this != &m)  // �Լ����ܸ����Լ�
	{
		delete[] element;
		theRows = m.theRows;
		theColumns = m.theColumns;
		element = new T[theRows * theColumns];
		// ����ÿ��Ԫ��
		copy(m.element, m.element + theRows * theColumns, element);
	}
	return *this;
}
/************����˵��*****************
* ��������T& operator()(int i, int j) const
* �����������������Ͳ���
* ��������ֵ��������Ϊ(i,j)�ľ���Ԫ�ص�����
* �������ܣ�Ϊ����()����ʾ�������������ز�����()

**/
template<class T>
T& matrix<T>::operator()(int i, int j) const
{
	if (i < 1 || i > theRows || j < 1 || j > theColumns)
		throw "matrix index out of bounds";
	return element[(i - 1) * theColumns + j - 1];
}
/************����˵��*****************
* ��������matrix<T> operator+(const matrix<T>& m)const
* ����������һ������ƥ��ľ���
* ��������ֵ��������Ӻ�ľ���
* �������ܣ�ʵ�־���ӷ������ز�����+

**/
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m)const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw "matrix size mismatch.";
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; ++i)  // ��Ϊ����ӳ�䵽һά���飬���������������ֻ��Ҫһ��forѭ��
		w.element[i] = element[i] + m.element[i];
	return w;
}

/************����˵��*****************
* ��������matrix<T> operator*(const matrix<T>& m)const
* ����������һ������ƥ��ľ���
* ��������ֵ��������˺�ľ���
* �������ܣ�ʵ�־���˷������ز�����*
* ˵������Ҫע����ǣ������������0��ʼ�������������1��ʼ����������������Ѿ���ӳ�䵽һ��һά�����С�
**/
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m)const
{
	if (theColumns != m.theRows)
		throw "matrix size mismatch";
	matrix<T> w(theRows, m.theColumns);  // �������
	// �������*this��m��w���α��ҳ�ʼ����Ϊ(1,1)Ԫ�ض�λ
	int ct = 0, cm = 0, cw = 0;

	// ������i��j����w(i, j)
	for (int i = 1; i <= theRows; i++)  // ��һ��������б���
	{
		// ����������ĵ�i��
		for (int j = 1; j <= m.theColumns; j++)  // �ڶ���������б���
		{
			// ����w(i,j)�ĵ�һ��
			T sum = element[ct] * m.element[cm];
			// �ۼ�����������
			for (int k = 2; k <= theColumns; k++)  // �� ��һ������ĵ�i�е�����Ԫ�� * �ڶ�������ĵ�j�е�����Ԫ�� �ۼ�
			{
				ct++;  // *this�е�i�е���һ��
				cm += m.theColumns;  // m�еĵ�j�е���һ���������ӳ��
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;  // �洢��w(i,j)
			// ���е�������һ�д��¿�ʼ
			ct -= theColumns - 1;
			cm = j;
		}
		// ����һ�к͵�һ�����¿�ʼ
		ct += theColumns;
		cm = 0;
	}
	return w;
}

template<class T>
matrix<T> matrix<T>::
operator-(const matrix<T>& m) const
{// Return (*this) - m.
	if (theRows != m.theRows
		|| theColumns != m.theColumns)
		throw "matrix size mismatch";

	// create result matrix w
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		w.element[i] = element[i] - m.element[i];

	return w;
}

template<class T>
matrix<T> matrix<T>::operator-() const
{// Return w = -(*this).

   // create result matrix w
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		w.element[i] = -element[i];
	return w;

}

template<class T>
matrix<T> matrix<T>::operator+() const
{// Return w = -(*this).

   // create result matrix w
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		w.element[i] = +element[i];
	return w;

}

template<class T>
matrix<T>& matrix<T>::operator+=(const T& x)
{// Increment all elements of *this by x.
	for (int i = 0; i < theRows * theColumns; i++)
		element[i] += x;
	return *this;
}
// Independent coding
// ����ת��
template<class T>
matrix<T> matrix<T>::trans()
{
	matrix<T> m(theColumns, theRows);
	matrix <T> n(*this);
	for (int i = 1; i <= theRows; ++i)
	{
		for (int j = 1; j <= theColumns; ++j)
		{

			m(j, i) = n(i, j);
		}

	}
	return m;
}

#endif // !__MATRIX_


// ������������
void testMain();



#ifndef __DIAGONALMATRIX_
#define __DIAGONALMATRIX_

/****************�ԽǾ���******************
* ������diagonalMatrix<T>
* ˵����һ��row*rows�ĶԽǾ���D�����ֻ��rows����0Ԫ�أ���˿�����һ��һά����element[rows]����ʾ�ԽǾ������У�
		element[i-1]��ʾD(i,i)������δ��һά�����г��ֵľ���Ԫ�ؾ�Ϊ0.
* ʱ�临�Ӷȣ����ڹ��캯����ʱ�临�Ӷ���˵����T���ڲ�����ʱΪO(1)����T���û���������ʱΪO(rows)��
			  ����get������set������ʱ�临�Ӷȶ���O(1)��

**/

template<class T>
class diagonalMatrix
{
public:
	diagonalMatrix(int theN = 10);
	~diagonalMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);

private:
	int n;  // ����ά����
	T* element;  // �洢�ԽǾ����һά����
};

// ���캯��
template <class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{
	// ����theN��ֵ�Ƿ���Ч
	if (theN < 1)
		throw "Matrix size must be > 0";
	n = theN;
	element = new T[n];
}

// get����
template <class T>
T diagonalMatrix<T>::get(int i, int j)const
{
	//��������Ƿ���Ч
	if (i < 1 || j < 1 || i > n || j > n)
		throw "matrix index out of bounds";
	else if (i == j)
		return element[i - 1];  // ���ضԽ����ϵ�Ԫ��
	else
		return 0;  // �ǶԽ����ϵ�Ԫ��
}

// set����
template<class  T>
void diagonalMatrix<T>::set(int i, int j, const T& x)
{
	//��������Ƿ���Ч
	if (i < 1 || j < 1 || i > n || j > n)
		throw "matrix index out of bounds";
	else if (i == j)
		element[i - 1] = x;
	else
		if (x != 0)
			throw "nondiagonal element must be zero";
}




#endif // !__DIAGONALMATRIX_



#ifndef __TRIDIAGONALMATRIX_
#define __TRIDIAGONALMATRIX_


/****************���ԽǾ���******************
* ������tridiagonalMatrix<T>
* ˵������һ��rows*rows�����ԽǾ����У���0Ԫ�����������������Խ����ϣ�
			1�����Խ��ߣ�`i = j`;
			2�����Խ���֮�µĶԽ��ߣ���Ϊ�ͶԽ��ߣ���`i = j + 1`;
			3�����Խ���֮�ϵĶԽ��ߣ���Ϊ�߶Խ��ߣ���`i = j - 1`;
		�������Խ��ߵ�Ԫ������Ϊ`3*rows-2`��������һ������Ϊ`3*rows-2`��һά����element���������ԽǾ���һ��������ӳ���ϵ��
			1������ӳ�䣻
			2������ӳ�䣻
			3���������������Խ��߿�ʼ�����Խ���ӳ�䡣
* ʱ�临�Ӷȣ����ڹ��캯����ʱ�临�Ӷ���˵����T���ڲ�����ʱΪO(1)����T���û���������ʱΪO(rows)��
			  ����get������set������ʱ�临�Ӷȶ���O(1)��

**/






template<class T>
class tridiagonalMatrix
{
public:
	tridiagonalMatrix(int theN = 10);
	~tridiagonalMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
private:
	int n;       // matrix dimension
	T* element;  // 1D array for tridiagonal
};

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T[3 * n - 2];
}

template <class T>
T tridiagonalMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.

   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	// determine lement to return
	switch (i - j)
	{
	case 1: // lower diagonal
		return element[i - 2];
	case 0: // main diagonal
		return element[n + i - 2];
	case -1: // upper diagonal
		return element[2 * n + i - 2];
	default: return 0;
	}
}

template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element

   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	switch (i - j)
	{
	case 1: // lower diagonal
		element[i - 2] = newValue; break;
	case 0: // main diagonal
		element[n + i - 2] = newValue; break;
	case -1: // upper diagonal
		element[2 * n + i - 2] = newValue; break;
	default: if (newValue != 0)
		throw illegalParameterValue
		("non-tridiagonal elements must be zero");
	}
}

#endif // !__TRIDIAGONALMATRIX_

#ifndef __LOWERTRAIANGULARMATRIX_
#define __LOWERTRAIANGULARMATRIX_
/**************�����Ǿ���**************
* ������lowerTriangularMatrix<T>
* ���˵����



**/

template<class T>
class lowerTriangularMatrix
{
public:
	lowerTriangularMatrix(int theN = 10);
	~lowerTriangularMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
private:
	int n;       // ����ά��
	T* element;  // һά����
};


template<class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T[n * (n + 1) / 2];
}

template <class T>
T lowerTriangularMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	// (i,j) in lower triangle iff i >= j
	if (i >= j)
		return element[i * (i - 1) / 2 + j - 1];
	else
		return 0;
}

template<class T>
void lowerTriangularMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();


	// (i,j) in lower triangle iff i >= j
	if (i >= j)
		element[i * (i - 1) / 2 + j - 1] = newValue;
	else
		if (newValue != 0)
			throw illegalParameterValue
			("elements not in lower triangle must be zero");
}

#endif // !__LOWERTRAIANGULARMATRIX_

#ifndef __SPAREMATRIX_
#define __SPAREMATRIX_

/****************ϡ�����***********
* ������
* ���˵����һ��m*n�ľ�����������Ԫ�ض���0�����Ϊϡ�����һ�������������ϡ��ģ��ͳ�Ϊ���ܾ��󡣸ò������ط�����0���򲻹����ϡ�����
* 


**/


#endif // !__SPAREMATRIX_


#endif