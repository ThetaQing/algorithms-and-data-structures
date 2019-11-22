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
	matrix<T> operator +=(const T&) ;  
	matrix<T> operator *(const matrix<T>&) const;


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



#endif