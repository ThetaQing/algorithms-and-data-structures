#ifndef __SPAREMATRIX_
#define __SPAREMATRIX_
#include <iostream>
#include "matrixTerm.h"
#include "extendedArrayList.h"
#include "myExceptions.h"
using namespace std;
/****************ϡ�����***********
* ������
* ���˵����һ��m*n�ľ�����������Ԫ�ض���0�����Ϊϡ�����һ�������������ϡ��ģ��ͳ�Ϊ���ܾ��󡣸ò������ط�����0���򲻹����ϡ�����
* ���÷�����
			1��reSet(newSize)���������Ԫ�ظ�����ΪnewSize����Ҫʱ��������������
			2��set(theIndex, theElement)��ʹ�����Ԫ��theElement��Ϊ��������ΪtheIndex��Ԫ�أ�
			3��clear()��ʹ���Ԫ�ظ���Ϊ0.


**/

template <class T>
class sparseMatrix
{
public:
	void transpose(sparseMatrix<T>& b);
	void add(sparseMatrix<T>& b, sparseMatrix<T>& c);
private:
	int rows;  // ��������
	int cols;  // ��������
	arrayList<matrixTerm<T>> terms;  // ��0���
};

// ������������ <<
// ��x���������
template <class T>
ostream& operator << (ostream& out, sparseMatrix<T>& x)
{
	// �����������
	out << "rows = " << x.rows << "  columns = " << x.cols << endl;
	out << "ninzero terms = " << x.terms.size() << endl;
	// ��������һ��һ��
	for (arrayList<matrixTerm<T>> ::iterator i = x.terms.begin(); i != x.terms.end(); ++i)  // ʹ�ô������ҵ�˳���������������������ȡ�����0Ԫ��
	{
		out << "a(" << (*i).row << ',' << (*i).col << ") = " << (*i).value << endl;
	}
	return out;
}

// ������������� >>
// ����һ��ϡ�����
template<class T>
istream& operator >> (istream& in, sparseMatrix<T>& x)
{
	// �����������
	int numberOfTerms;
	cout << "Enter number of rows, columns, and #terms" << endl;
	in >> x.rows >> x.cols >> numberOfTerms;
	// �������ĺϷ���
	if (x.rows < 0 || x.cols < 0 || numberOfTerms < 0)
		throw "number of rows, columns, and #terms must > 0";

	// ����x.terms�Ĵ�С��ȷ���㹻������
	x.terms.reSet(numberOfTerms);
	// ������
	matrixTerm<T> mTerm;
	for (int i = 0; i < numberOfTerms; ++i)
	{
		cout << "Enter row, column, and value of term " << (i + 1) << endl;
		in >> mTerm.row >> mTerm.col >> mTerm.value;

		// �������ĺϷ���
		if (mTerm.row > x.rows || mTerm.col > x.cols)
			throw "the term's rows or columns must <= the matrix's rows or columns";

		x.terms.set(i, mTerm);
	}
	return in;
}
/****************����˵��**********************
* ��������transpose(sparseMatrix<T>& b)
* ����������ת�ú�ľ���
* ��������ֵ������b��*this��ת��
* ����ʵ�֣�ת�ú�ľ���洢�ھ���b�У���������b��������������Ȼ��ʹ���Ա�b.terms��Ԫ�ظ������ڱ�ת�þ����Ԫ�ظ�������ˣ�ʵ�����ǰ�
			���Ա���Ϊһ��һά���飬һ��ʼ��Ԫ�ظ��������������Ԫ�ظ�����Ȼ��ͨ��set��������һ��λ�ø�һ����ֵ��
			�������Ǵ�����������colSize��rowNext��colSize[i]���������*this�ڵ�i�еķ�0Ԫ�ظ�����rowNext[i]��ת�þ����i���׸���0Ԫ����b�����ת�ú�ľ����е�������
			��colSize�ļ�����ǰ����forѭ������ɣ�ʹ�õ����������ÿ���������Ԫ�ء���rowNext�ļ����ڵ�����forѭ������ɣ�rowNext[i]��ֵ��ת�þ���b�ĵ�0������i-1�е�Ԫ�ظ�������
			�������*this�ĵ�0������i-1�е�Ԫ�ظ�����
			�����һ��forѭ���У���0Ԫ�ر����Ƶ�b����Ӧλ�á�

// ����ת��
**/

template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>& b)
{// ����b��*this��ת��

   // ���þ�������
	b.cols = rows;
	b.rows = cols;
	b.terms.reSet(terms.size());

	// ��ʼ����ʵ��ת��
	int* colSize = new int[cols + 1];
	int* rowNext = new int[cols + 1];

	// Ѱ��*this��ÿһ�е������Ŀ
	for (int i = 1; i <= cols; i++) // ��ʼ��
		colSize[i] = 0;
	for (arrayList<matrixTerm<T> >::iterator i = terms.begin();
		i != terms.end(); i++)  // ʹ�õ��������ڷ�0Ԫ�����ڵ��м���+1
		colSize[(*i).col]++;

	// Ѱ��b��ÿһ�е���ʼ��
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
/*****************����˵��**********************
* ��������add(sparseMatrix<T>& b, sparseMatrix<T>& c)
* ������������һ����������*this������ӵľ���b���ڶ������������֮��ĺ;���c
* ��������ֵ��c����
* �������ܣ�����c = *this + b
* ����ʵ�֣�ͨ����������ɨ��*this��b�ķ�0����ʵ�ֵġ�
			1����ɨ�������ʹ�þ���*this�ĵ�����it�;���b�ĵ�����ib��
			2����whileѭ����ÿһ�ε����У���Ҫ�����������������*it������С�ڡ����ڡ�����*ib��������
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