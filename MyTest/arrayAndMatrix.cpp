#include <iostream>
#include "arrayAndMatrix.h"

using namespace std;

/*****************�ļ�����********************
* �ļ�����arrayAndMatrix.cpp
* �ļ����ܣ������ݽṹ�������� ���������




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

}
