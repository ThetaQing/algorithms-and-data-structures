#ifndef __BIN_SORT_H__
#define __BIN_SORT_H__
#include <string>
#include "linear_list.h"
using namespace std;
/*************�ļ�˵��****************
* �ļ�����bin_sort.h
* �ļ����ܣ�ʵ����������
* ��Ҫ���裺
		1�����ɾ����������Ľڵ㣬��ɾ���Ľڵ���䵽��Ӧ�������
		2����ÿһ�������е������ռ�������������ʹ���Ϊһ����������

**/

// �ṹ�嶨��
struct studentRecord
{
	int score;
	std::string* name;
	/*
	int operator != (const studentRecord& x)const  // ��������� ��=,����studentRecord����ת��Ϊ��ֵ���ͣ���ʵ�ֱȽϲ���������Ŀ��
	{
		return (score != x.score);
	}
	*/	
	operator int() const  // ��������ת��������int()�����������͹�ϵ��������Ȼû�����ػ���ȷ���壬���ǿ���ͨ��int()����ת��������ת����int������ɲ���
	{
		return score;
	}
	studentRecord() {};
	studentRecord(string* name, int score)
	{
		this->name = name;
		this->score = score;
	}
	
};

/*************����˵��****************

* ��������
* ����������
* ��������ֵ��
* �������ܣ����������<<
ostream& operator<<(ostream& out, const studentRecord& x)  // ��������� <<
{
	out << x.score << ' ' << *x.name << endl;
	return out;

}*/

/****************************************
==========================================
* ������unionFindWithArray
* �๦�ܣ�����ʵ�ֺϲ����ĺϲ�������
* ��ĳ�Ա��
	void initialize(int numberOfElement);  // ��ʼ������
	void unite(int classA, int classB);  // �ϲ�����

	int find(int theElement); // ���Һ���
	void testMain();  // ���Ժ���

==========================================
*/
class unionFindWithArray
{
public:


	void initialize(int numberOfElement);

	void unite(int classA, int classB);

	int find(int theElement);
	void testMain(void);
private:
	int* equivClass, n;  // �ֱ��ʾ�ȼ��������Ԫ�ظ���
};


// ������������
void binSort2(chain<studentRecord>& theChain, int range);
void testUnionFindWithArrays(void);
// ����ڵ�Ľṹ������
struct  equivNode
{
	int equivClass;  // Ԫ�����ʶ��
	int size; // ���Ԫ�ظ���
	int next;  // ����ָ����һ��Ԫ�ص�ָ��
};
/****************************************
==========================================
* ������unionFindWithChains
* �๦�ܣ� ����ʵ�ֺϲ����ĺϲ�������
* ��ĳ�Ա��
	void initialize(int numberOfElement);  // ��ʼ������
	void unite(int classA, int classB);  // �ϲ�����
	 
	int find(int theElement); // ���Һ���
	void testMain();  // ���Ժ���

==========================================
*/

class unionFindWithChains
{
public:
	void initialize(int numberOfElement);  // ��ʼ������
	void unite(int classA, int classB);  // �ϲ�����
	 
	int find(int theElement); // ���Һ���
	void testMain();  // ���Ժ���

private:
	equivNode* node;  // �ڵ������
	int n; // Ԫ�ظ���
};
#endif // !__BIN_SORT_H__
#pragma once
