#ifndef __DIAGONALMATRIX_
#define __DIAGONALMATRIX_
#include "arrayAndMatrix.h"
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
