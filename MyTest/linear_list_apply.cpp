#include <iostream>
#include "linear_list_apply.h"
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
**/
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
}
/************************************
=====================================

* �����ţ�6-19 ���ݽṹ P140
* �����ܣ�ʹ������ʵ�ֵĲ��鼯�㷨
* ȫ�ֱ�����int* equivClass, n;   �ֱ��ʾ�ȼ��������Ԫ�ظ���
* ˵��������equivClass��equivClass[i]Ϊ����Ԫ��i�ĵȼ���
* ʱ�临�Ӷȣ�ͨ��ִ��һ�γ�ʼ����u�κϲ���f�β��ң�ʱ�临�Ӷ�ΪO(n+u*n+f)
=====================================

**/

int* equivClass, n;  // �ֱ��ʾ�ȼ��������Ԫ�ظ���
/******************����˵��**********************

* ��������void initialize(int numberOfElement)
* ����������Ԫ�ظ���
* ��������ֵ:��
* �������ܣ���ÿ�����һ��Ԫ�أ���ʼ��numberOfElements����
* ʱ�临�Ӷȣ�O(n)


**/


void initialize(int numberOfElement)
{
	n = numberOfElement;
	equivClass = new int[n + 1];
	for (int e = 1; e <= n; ++e)  // ����ǰ���0��Ȼ��˳������
	{
		equivClass[e] = e;
	}
}

/*******************����˵��********************

* ��������void unite(int classA, int classB)
* ����������������ͬ����classA��classB
* ��������ֵ���գ�ȫ��ָ�뷵���������unite������
* �������ܣ��ϲ���classA��classB����classB��Ԫ��ȫ���ϲ���ΪclassA��
* ʱ�临�Ӷȣ�O(n)

**/
void unite(int classA, int classB)
{
	for (int k = 1; k <= n; ++k)  // �κ�classA ��= classB
	{
		if (equivClass[k] == classB)  // �ҵ�����classB�е�Ԫ�أ�����ЩԪ��ȫ���ϲ���classA����
			equivClass[k] = classA;
	}

}
/*******************����˵��********************

* ��������int find(int theElement)
* ����������������Ԫ��
* ��������ֵ�����ؾ������Ԫ�ص���
* �������ܣ����Ҿ���Ԫ��theElement����
* ʱ�临�Ӷȣ�O(1)
**/
int find(int theElement)
{
	return equivClass[theElement];
}

/*******************����˵��*******************
* ��������void testUnionFindWithArrays(void)
* ������������
* ��������ֵ����
* �������ܣ���6-19������в���

**/
void testUnionFindWithArrays(void)
{
	initialize(10);
	unite(1, 2);  // ִ�к�1��2��ΪequivClass[1]��
	unite(3, 4);  // ִ�к�3��4��ΪequivClass[3]��
	unite(1, 3);  // ִ��ǰ��3��4��ΪequivClass[3]�ִ࣬�к�3��4��ΪequivClass[1]�ࡣ
	for (int i = 1; i < 10; ++i)
	{
		cout << "Element " << i << " is in equivalence class " << find(i) << endl;
	}
}



