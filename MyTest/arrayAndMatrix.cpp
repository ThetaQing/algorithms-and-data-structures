#include <iostream>
#include "arrayAndMatrix.h"
#include "diagonalMatrix.h"
#include "overloadOperator.h"
using namespace std;

/*****************�ļ�����********************
* �ļ�����arrayAndMatrix.cpp
* �ļ����ܣ������ݽṹ�������� ���������




**/



void testMain()
{
	matrix<int> m(3,4);  // ָ�����й���
	for(int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 4; ++j)
		{
			m(i, j) = (i - 1) * 4 + j;
		}

	matrix <int> n(m);  // ���ƹ��캯��
	matrix<int> test;
	test = m + n; // �ӷ�
	cout << "test of +" << endl;
	cout << test;
	cout << "test of -" << endl;
	test = m - n; // ����
	cout << test;

	cout << "test of - ����Ŀ���㣩" << endl;
	test = -m ; // test of - ����Ŀ���㣩
	cout << test;

	cout << "test of trans" << endl;
	test = m.trans(); // ת������
	cout << test;

	test = m * test  ;  // �˷�
	cout << "test of trans" << endl;
	
	cout << test;
	cout << "*****************�ԽǾ������*******************" << endl;
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

	cout << "**********************���ԽǾ������******************" << endl;
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
	===============����ʧ��===============
	cout << "**********************ϡ��������******************" << endl;
	sparseMatrix<int> sm1,sm2,sm;
	cin >> sm1;
	cin >> sm2;
	cin >> sm;
	sm.transpose(sm);
	cout << "ת��֮���sm����" << endl;
	cout << sm;
	sm1.add(sm2, sm);
	cout << "smΪsm1+sm2�ĺ;���" << endl;
	cout << sm;

	*/
}
