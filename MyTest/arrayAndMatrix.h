#ifndef __ARRAYANDMATRIX_H__
#define __ARRAYANDMATRIX_H__

#include <iostream>
#include <sstream>
#include "myExceptions.h"
using namespace std;
/*****************文件描述********************
* 文件名：arrayAndMatrix.h
* 文件功能：《数据结构》第七章 数组与矩阵


**/

#ifndef __MATRIX_
#define __MATRIX_
/********************程序说明*******************
=================================================

* 程序编号：7-2  P153
* 程序功能：矩阵类matrix的声明与实现
* 类的成员函数：
			1、构造函数（默认构造函数和复制构造函数）；
			2、析构函数；
			3、返回行数的函数；
			4、返回列数的函数；
			5、重载运算符=、+、-、（）、*
			6、转置运算


=================================================
**/

/****************程序说明***********
* 程序功能：matrix类的声明


*/
template<class T>
class matrix
{
	friend ostream& operator<< (ostream&, const matrix<T>&);
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>&);
	~matrix() { delete[] element; }
	int rows() const { return theRows; };  // 返回行数的函数
	int columns() const { return theColumns; }  // 返回列数的函数
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

#endif // !__MATRIX_


// 其他函数声明
void testMain();



#ifndef __DIAGONALMATRIX_
#define __DIAGONALMATRIX_

/****************对角矩阵******************
* 类名：diagonalMatrix<T>
* 说明：一个row*rows的对角矩阵D，最多只有rows个非0元素，因此可以用一个一维数组element[rows]来表示对角矩阵，其中，
		element[i-1]表示D(i,i)，所有未在一维数组中出现的矩阵元素均为0.
* 时间复杂度：对于构造函数的时间复杂度来说，当T是内部类型时为O(1)，当T是用户定义类型时为O(rows)；
			  对于get方法和set方法的时间复杂度都是O(1)。

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
	int n;  // 矩阵维数；
	T* element;  // 存储对角矩阵的一维数组
};

// 构造函数
template <class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{
	// 检验theN的值是否有效
	if (theN < 1)
		throw "Matrix size must be > 0";
	n = theN;
	element = new T[n];
}

// get方法
template <class T>
T diagonalMatrix<T>::get(int i, int j)const
{
	//检验参数是否有效
	if (i < 1 || j < 1 || i > n || j > n)
		throw "matrix index out of bounds";
	else if (i == j)
		return element[i - 1];  // 返回对角线上的元素
	else
		return 0;  // 非对角线上的元素
}

// set方法
template<class  T>
void diagonalMatrix<T>::set(int i, int j, const T& x)
{
	//检验参数是否有效
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


/****************三对角矩阵******************
* 类名：tridiagonalMatrix<T>
* 说明：在一个rows*rows的三对角矩阵中，非0元素排列在如下三条对角线上：
			1、主对角线：`i = j`;
			2、主对角线之下的对角线（称为低对角线）：`i = j + 1`;
			3、主对角线之上的对角线（称为高对角线）：`i = j - 1`;
		这三条对角线的元素总数为`3*rows-2`，可以用一个容量为`3*rows-2`的一维数组element来描述三对角矩阵；一共有三种映射关系：
			1、逐行映射；
			2、逐列映射；
			3、从最下面那条对角线开始逐条对角线映射。
* 时间复杂度：对于构造函数的时间复杂度来说，当T是内部类型时为O(1)，当T是用户定义类型时为O(rows)；
			  对于get方法和set方法的时间复杂度都是O(1)。

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
/**************下三角矩阵**************
* 类名：lowerTriangularMatrix<T>
* 类的说明：



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
	int n;       // 矩阵维数
	T* element;  // 一维数组
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

/****************稀疏矩阵***********
* 类名：
* 类的说明：一个m*n的矩阵，如果大多数元素都是0，则称为稀疏矩阵，一个矩阵如果不是稀疏的，就称为稠密矩阵。该部分着重分析非0区域不规则的稀疏矩阵。
* 内置方法：
			1、reSet(newSize)：把数组的元素个数改为newSize，必要时增大数组容量；
			2、set(theIndex, theElement)：使数组的元素theElement成为表中索引为theIndex的元素；
			3、clear()：使表的元素个数为0.


**/

#ifndef matrixTerm_
#define matrixTerm_
#include "extendedArrayList.h"
// 定义结构体，存储非0项的行、列、及元素值
template <class T>
struct matrixTerm
{
	int row,
		col;
	T value;

	operator T() const { return value; }
	// type conversion from matrixTerm to T
};

#endif

template <class T>
class sparseMatrix
{
public:
	void transpose(sparseMatrix<T>& b);
	void add(sparseMatrix<T>& b, sparseMatrix<T>& c);
private:
	int rows;  // 矩阵行数
	int cols;  // 矩阵列数
	arrayList<matrixTerm<T>> terms;  // 非0项表
};

// 重载输出运算符 <<
// 将x放入输出流
template <class T>
ostream& operator << (ostream& out, sparseMatrix<T>& x)
{
	// 输出矩阵特征
	out << "rows = " << x.rows << "  columns = " << x.cols << endl;
	out << "ninzero terms = " << x.terms.size() << endl;
	// 输出矩阵项，一行一个
	for (arrayList<matrixTerm<T>> ::iteration i = x.terms.begin(); i != x.terms.end(); ++i)  // 使用从左往右的顺序迭代器，按行主次序提取矩阵非0元素
	{
		out << "a(" << (*i).row << ',' << (*i).col << ") = " << (*i).value << endl;
	}
	return out;
}

// 重载输入操作符 >>
// 输入一个稀疏矩阵
template<class T>
istream& operator >> (istream& in, sparseMatrix<T>& x)
{
	// 输入矩阵特征
	int numberOfTerms;
	cout << "Enter number of rows, columns, and #terms" << endl;
	in >> x.rows >> x.cols >> numberOfTerms;
	// 检查输入的合法性
	if (x.rows < 0 || x.cols < 0 || numberOfTerms < 0)
		throw "number of rows, columns, and #terms must > 0";

	// 设置x.terms的大小，确保足够的容量
	x.terms.reSet(numberOfTerms);
	// 输入项
	matrixTerm<T> mTerm;
	for (int i = 0; i < numberOfTerms; ++i)
	{
		cout << "Enter row, column, and value of term " << (i + 1) << endl;
		in >> mTerm.row >> mTerm.col >> mTerm.value;

		// 检查输入的合法性
		if (mTerm.row > x.rows || mTerm.col > x.cols)
			throw "the term's rows or columns must <= the matrix's rows or columns";

		x.terms.set(i, mTerm);
	}
	return in;
}
/****************函数说明**********************
* 函数名：transpose(sparseMatrix<T>& b)
* 函数参数：转置后的矩阵
* 函数返回值：返回b中*this的转置
* 函数实现：转置后的矩阵存储在矩阵b中，首先设置b的行数和列数，然后使线性表b.terms的元素个数等于被转置矩阵的元素个数。因此，实质上是吧
			线性表作为一个一维数组，一开始的元素个数等于它最早的元素个数，然后通过set方法给任一个位置赋一个新值。
			接下来是创建两个数组colSize和rowNext。colSize[i]是输入矩阵*this在第i列的非0元素个数，rowNext[i]是转置矩阵第i行首个非0元素在b（这个转置后的矩阵）中的索引。
			对colSize的计算在前两个for循环中完成：使用迭代器，检查每个输入矩阵元素。对rowNext的计算在第三个for循环中完成：rowNext[i]的值是转置矩阵b的第0行至第i-1行的元素个数，即
			输入矩阵*this的第0列至第i-1列的元素个数。
			在最后一个for循环中，非0元素被复制到b中相应位置。

// 矩阵转置
**/

template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>& b)
{// 返回b中*this的转置

   // 设置矩阵特征
	b.cols = rows;
	b.rows = cols;
	b.terms.reSet(terms.size());

	// 初始化以实现转置
	int* colSize = new int[cols + 1];
	int* rowNext = new int[cols + 1];

	// 寻找*this中每一列的项的数目
	for (int i = 1; i <= cols; i++) // 初始化
		colSize[i] = 0;
	for (arrayList<matrixTerm<T> >::iterator i = terms.begin();
		i != terms.end(); i++)  // 使用迭代器，在非0元素所在的列计数+1
		colSize[(*i).col]++;

	// 寻找b中每一行的起始点
	rowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];

	// perform the transpose copying from *this to b
	matrixTerm<T> mTerm;
	for (arrayList<matrixTerm<T> >::iterator i = terms.begin();
		i != terms.end(); i++)
	{
		int j = rowNext[(*i).col]++; // position in b
		mTerm.row = (*i).col;
		mTerm.col = (*i).row;
		mTerm.value = (*i).value;
		b.terms.set(j, mTerm);
	}
}
/*****************函数说明**********************
* 函数名：add(sparseMatrix<T>& b, sparseMatrix<T>& c)
* 函数参数：第一个参数是与*this矩阵相加的矩阵b，第二个参数是相加之后的和矩阵c
* 函数返回值：c矩阵
* 函数功能：计算c = *this + b
* 函数实现：通过从左往右扫描*this和b的非0项来实现的。
			1、在扫描过程中使用矩阵*this的迭代器it和矩阵b的迭代器ib；
			2、在while循环的每一次迭代中，需要区分三种情况来处理：*it的索引小于、等于、大于*ib的索引；
**/
template<class T>
void sparseMatrix<T>::add(sparseMatrix<T>& b, sparseMatrix<T>& c)
{// Compute c = (*this) + b.

   // verify compatibility
	if (rows != b.rows || cols != b.cols)
		throw matrixSizeMismatch(); // incompatible matrices

	  // set characteristics of result c
	c.rows = rows;
	c.cols = cols;
	c.terms.clear();
	int cSize = 0;

	// define iterators for *this and b
	arrayList<matrixTerm<T> >::iterator it = terms.begin();
	arrayList<matrixTerm<T> >::iterator ib = b.terms.begin();
	arrayList<matrixTerm<T> >::iterator itEnd = terms.end();
	arrayList<matrixTerm<T> >::iterator ibEnd = b.terms.end();

	// move through *this and b adding like terms
	while (it != itEnd && ib != ibEnd)
	{
		// row-major index plus cols of each term
		int tIndex = (*it).row * cols + (*it).col;
		int bIndex = (*ib).row * cols + (*ib).col;

		if (tIndex < bIndex)
		{// b term comes later
			c.terms.insert(cSize++, *it);
			it++;
		}
		else {
			if (tIndex == bIndex)
			{// both in same position

			   // append to c only if sum not zero
				if ((*it).value + (*ib).value != 0)
				{
					matrixTerm<T> mTerm;
					mTerm.row = (*it).row;
					mTerm.col = (*it).col;
					mTerm.value = (*it).value + (*ib).value;
					c.terms.insert(cSize++, mTerm);
				}

				it++;
				ib++;
			}
			else
			{// a term comes later
				c.terms.insert(cSize++, *ib);
				ib++;
			}
		}
	}

	// copy over remaining terms
	for (; it != itEnd; it++)
		c.terms.insert(cSize++, *it);
	for (; ib != ibEnd; ib++)
		c.terms.insert(cSize++, *ib);
}


#endif // !__SPAREMATRIX_


#endif