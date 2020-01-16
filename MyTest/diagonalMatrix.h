#ifndef __DIAGONALMATRIX_
#define __DIAGONALMATRIX_
#include "arrayAndMatrix.h"
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
