#include <iostream>
#include "arrayAndMatrix.h"

using namespace std;

/*****************文件描述********************
* 文件名：arrayAndMatrix.cpp
* 文件功能：《数据结构》第七章 数组与矩阵




**/

// for some reason compiler can't create this on its own
ostream& operator<<(ostream& out, const matrix<int>& m)
{// Put matrix m into the stream out.
 // One row per line.

	int k = 0;  // index into element array
	for (int i = 0; i < m.theRows; i++)
	{// do row i
		for (int j = 0; j < m.theColumns; j++)
			out << m.element[k++] << "  ";

		// row i finished
		out << endl;
	}

	return out;
}

void testMain()
{
	matrix<int> m(3,4);  // 指定行列构造
	for(int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 4; ++j)
		{
			m(i, j) = (i - 1) * 4 + j;
		}

	matrix <int> n(m);  // 复制构造函数
	matrix<int> test;
	test = m + n; // 加法
	cout << "test of +" << endl;
	cout << test;
	cout << "test of -" << endl;
	test = m - n; // 减法
	cout << test;

	cout << "test of - （单目运算）" << endl;
	test = -m ; // test of - （单目运算）
	cout << test;

	cout << "test of trans" << endl;
	test = m.trans(); // 转置运算
	cout << test;

	test = m * test  ;  // 乘法
	cout << "test of trans" << endl;
	
	cout << test;

}
