#include <iostream>
#include "bin_sort.h"
#include "linear_list.h"
using namespace std;
/***********�ļ�˵��************
* �ļ�����bin_sort.cpp����������
* �ļ����ܣ�ʵ���������򣬶�ѧ���ɼ���С��������

**/

/****************����˵��************************
* �������� void binSort(chain<studentRecord>& theChain, int range)
* ����������һ����¼ѧ���ɼ��������ɼ����뷶Χ
* ��������ֵ����ַ���ݣ���С���������ѧ���ɼ�����
* �������ܣ�ʹ������Ķ������������������
* ʵ�ֲ��裺
		1������ɾ���������Ԫ�أ���������������Ӧ��ĳ�����ӵ�������λ��
		2�������һ�����ӿ�ʼ�����մ�С�������򣩣����ɾ��ÿ�����ӵ�Ԫ�أ����������һ����ʼΪ�յ��������λ
* ʱ�临�Ӷȣ�����������ڴ�����쳣�Ļ�����һ��forѭ��O(n)���ڶ���forѭ��O(range)���ܵ�ʱ�临�Ӷ�O(n+range)

void binSort2(chain<studentRecord>& theChain, int range)
{
	// ����������

	// �����ӳ�ʼ��
	chain<studentRecord>* bin;
	bin = new chain<studentRecord>[range + 1];  // ÿһ��������һ�������ʾ

	// ��ѧ����¼��������ȡ����Ȼ����䵽������
	int numberOfElements = theChain.size();
	for (int i = 1; i <= numberOfElements; ++i)
	{
		studentRecord x = theChain.get(0);  // ���������ˣ������Ļ�get��insert��erase������ֻ��ҪO(1)��ʱ��
		theChain.erase(0);
		bin[x.score].insert(0, x);  // ������һ������ṹ
	}

	// ���������ռ�Ԫ��
	for (int j = range; j >= 0; --j)  // �����һ�����ӿ�ʼ����С�����˳��
	{
		while (!bin[j].empty())  // ����������
		{
			studentRecord x = bin[j].get(0);
			bin[j].erase(0);
			theChain.insert(0, x);  // ������ջ��һֱ�ӱ�ͷѹ�룬���������
		}
	}
	delete[] bin;  // �ͷ��ڴ�
}**/


