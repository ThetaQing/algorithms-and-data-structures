#ifndef __SPAREMATRIX_
#define __SPAREMATRIX_
#include <iostream>
#include "matrixTerm.h"
#include "extendedArrayList.h"
#include "myExceptions.h"
using namespace std;
/****************稀疏矩阵***********
* 类名：
* 类的说明：一个m*n的矩阵，如果大多数元素都是0，则称为稀疏矩阵，一个矩阵如果不是稀疏的，就称为稠密矩阵。该部分着重分析非0区域不规则的稀疏矩阵。
* 内置方法：
			1、reSet(newSize)：把数组的元素个数改为newSize，必要时增大数组容量；
			2、set(theIndex, theElement)：使数组的元素theElement成为表中索引为theIndex的元素；
			3、clear()：使表的元素个数为0.


**/

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
	for (arrayList<matrixTerm<T>> ::iterator i = x.terms.begin(); i != x.terms.end(); ++i)  // 使用从左往右的顺序迭代器，按行主次序提取矩阵非0元素
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