#ifndef __ARRAYANDMATRIX_H__
#define __ARRAYANDMATRIX_H__

#include <iostream>
#include <sstream>
using namespace std;
/*****************�ļ�����********************
* �ļ�����arrayAndMatrix.h
* �ļ����ܣ������ݽṹ�������� ���������


**/


/********************����˵��*******************
=================================================

* �����ţ�7-2  P153
* �����ܣ�������matrix������


=================================================
**/

/****************����˵��***********
* �����ܣ�matrix���˵��


*/
template<class T>
class matrix
{
	friend ostream& operator<< (ostream&, const matrix<T>&);
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>&);
	~matrix() { delete[] element; }
	int rows() const { return theRows; };
	int columns() const { return theColumns; }
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

// ������������
void testMain();

#endif



