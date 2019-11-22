#ifndef __ARRAYANDMATRIX_H__
#define __ARRAYANDMATRIX_H__

#include <iostream>
#include <sstream>
using namespace std;
/*****************文件描述********************
* 文件名：arrayAndMatrix.h
* 文件功能：《数据结构》第七章 数组与矩阵


**/


/********************程序说明*******************
=================================================

* 程序编号：7-2  P153
* 程序功能：矩阵类matrix的声明


=================================================
**/

/****************程序说明***********
* 程序功能：matrix类的说明


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
	matrix<T> operator +() const;  // 单目运算符+
	matrix<T> operator +(const matrix<T>&) const;
	matrix<T> operator -() const;  // 单目运算符-
	matrix<T> operator -(const matrix<T>&) const;
	matrix<T> operator +=(const T&) ;  
	matrix<T> operator *(const matrix<T>&) const;


private:
	int theRows;  // 矩阵的行数
	int theColumns;  // 矩阵的列数
	T* element;  // 数组element
};

/*****************函数说明*************************
* 函数名：matrix(int theRows, int theColumns)
* 函数参数：新建矩阵的行数和列数
* 函数返回值：一个theRows*theColumns的矩阵
* 函数功能：矩阵构造函数
* 注意：构造函数不仅生成行数和列数都大于0的矩阵，也生成0*0的矩阵

**/
template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
	// 检验行数和列数的有效性
	if (theRows < 0 || theColumns < 0)
		throw "Rows and columns must be >= 0";
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
		throw "Either both or neither rows and columns should be zero";
	// 创建矩阵
	this->theColumns = theColumns;
	this->theRows = theRows;
	element = new T[theRows * theColumns];
}
/*****************函数说明*************************
* 函数名：matrix(const matrix<T>& m)
* 函数参数：原矩阵
* 函数返回值：一个和原矩阵一样的矩阵
* 函数功能：矩阵的复制构造函数
* 注意：构造函数不仅生成行数和列数都大于0的矩阵，也生成0*0的矩阵

**/
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
	// 创建矩阵
	theRows = m.theRows;
	theColumns = m.theColumns;
	element = new T[theRows * theColumns];

	// 复制m的每个元素
	copy(m.element, m.element + theRows * theColumns, element);  // 第一个参数：开始复制的元素地址；第二个参数：最后一个复制的元素地址；第三个参数：目的地的起始地址
}
/************函数说明*****************
* 函数名：matrix<T>& operator=(const matrix<T>& m)
* 函数参数：一个矩阵
* 函数返回值：矩阵
* 函数功能：重载赋值运算符=

**/
template <class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	if (this != &m)  // 自己不能复制自己
	{
		delete[] element;
		theRows = m.theRows;
		theColumns = m.theColumns;
		element = new T[theRows * theColumns];
		// 复制每个元素
		copy(m.element, m.element + theRows * theColumns, element);
	}
	return *this;
}



#endif