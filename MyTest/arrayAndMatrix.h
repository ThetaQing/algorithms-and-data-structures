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
	matrix<T>& operator +=(const T&);  
	matrix<T> operator *(const matrix<T>&) const;
	
	// 转置运算
	matrix<T> trans();

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
/************函数说明*****************
* 函数名：T& operator()(int i, int j) const
* 函数参数：两个整型参数
* 函数返回值：对索引为(i,j)的矩阵元素的引用
* 函数功能：为了用()来表示矩阵索引，重载操作符()

**/
template<class T>
T& matrix<T>::operator()(int i, int j) const
{
	if (i < 1 || i > theRows || j < 1 || j > theColumns)
		throw "matrix index out of bounds";
	return element[(i - 1) * theColumns + j - 1];
}
/************函数说明*****************
* 函数名：matrix<T> operator+(const matrix<T>& m)const
* 函数参数：一个行列匹配的矩阵
* 函数返回值：返回相加后的矩阵
* 函数功能：实现矩阵加法，重载操作符+

**/
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m)const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw "matrix size mismatch.";
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; ++i)  // 因为矩阵被映射到一维数组，所以两个矩阵相加只需要一层for循环
		w.element[i] = element[i] + m.element[i];
	return w;
}

/************函数说明*****************
* 函数名：matrix<T> operator*(const matrix<T>& m)const
* 函数参数：一个行列匹配的矩阵
* 函数返回值：返回相乘后的矩阵
* 函数功能：实现矩阵乘法，重载操作符*
* 说明：需要注意的是，数组的索引从0开始，矩阵的索引从1开始，并且用行主次序把矩阵映射到一个一维数组中。
**/
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m)const
{
	if (theColumns != m.theRows)
		throw "matrix size mismatch";
	matrix<T> w(theRows, m.theColumns);  // 结果矩阵
	// 定义矩阵*this，m和w的游标且初始化以为(1,1)元素定位
	int ct = 0, cm = 0, cw = 0;

	// 对所有i和j计算w(i, j)
	for (int i = 1; i <= theRows; i++)  // 第一个矩阵的行遍历
	{
		// 计算结果矩阵的第i行
		for (int j = 1; j <= m.theColumns; j++)  // 第二个矩阵的列遍历
		{
			// 计算w(i,j)的第一项
			T sum = element[ct] * m.element[cm];
			// 累加其余所有项
			for (int k = 2; k <= theColumns; k++)  // 将 第一个矩阵的第i行的所有元素 * 第二个矩阵的第j列的所有元素 累加
			{
				ct++;  // *this中第i行的下一项
				cm += m.theColumns;  // m中的第j列的下一项，行主次序映射
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;  // 存储在w(i,j)
			// 从行的起点和下一列从新开始
			ct -= theColumns - 1;
			cm = j;
		}
		// 从下一行和第一列重新开始
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
// 计算转置
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

// 其他函数声明
void testMain();

#endif



