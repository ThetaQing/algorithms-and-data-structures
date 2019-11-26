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
* ���÷�����
			1��reSet(newSize)���������Ԫ�ظ�����ΪnewSize����Ҫʱ��������������
			2��set(theIndex, theElement)��ʹ�����Ԫ��theElement��Ϊ��������ΪtheIndex��Ԫ�أ�
			3��clear()��ʹ���Ԫ�ظ���Ϊ0.


**/

#ifndef matrixTerm_
#define matrixTerm_
#include "extendedArrayList.h"
// ����ṹ�壬�洢��0����С��С���Ԫ��ֵ
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
	for (arrayList<matrixTerm<T>> ::iteration i = x.terms.begin(); i != x.terms.end(); ++i)  // ʹ�ô������ҵ�˳���������������������ȡ�����0Ԫ��
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


#endif