#include <iostream>
#include "arrayAndMatrix.h"
#include "diagonalMatrix.h"
#include "overloadOperator.h"
using namespace std;

/*****************文件描述********************
* 文件名：arrayAndMatrix.cpp
* 文件功能：《数据结构》第七章 数组与矩阵




**/



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
	cout << "*****************对角矩阵测试*******************" << endl;
	diagonalMatrix<int> dm(4);
	for (int i = 1; i <= 4; ++i)
	{
		dm.set(i, i, i);
	}
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 4; ++j)
		{
			cout << dm.get(i, j) << "\t";
		}
		cout << endl;
	}

	cout << "**********************三对角矩阵测试******************" << endl;
	tridiagonalMatrix<int> tm(5);
	for (int i = 2; i <= 4; ++i)
	{
		tm.set(i, i + 1, 3);
		tm.set(i, i, 2);
		tm.set(i, i - 1, 1);
	}
	tm.set(1, 2, 3);
	tm.set(1, 1, 2);
	tm.set(2, 1, 1);
	tm.set(5, 5, 2);
	tm.set(5, 4, 1);
	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 1; j <= 5; ++j)
		{
			cout << tm.get(i, j) << "\t";
		}
		cout << endl;
	}

	/******************************************
	===============测试失败===============
	cout << "**********************稀疏矩阵测试******************" << endl;
	sparseMatrix<int> sm1,sm2,sm;
	cin >> sm1;
	cin >> sm2;
	cin >> sm;
	sm.transpose(sm);
	cout << "转置之后的sm矩阵" << endl;
	cout << sm;
	sm1.add(sm2, sm);
	cout << "sm为sm1+sm2的和矩阵" << endl;
	cout << sm;

	*/
}
