#ifndef __BIN_SORT_H__
#define __BIN_SORT_H__
#include <string>

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
	}*/	
	operator int() const  // ��������ת��������int()�����������͹�ϵ��������Ȼû�����ػ���ȷ���壬���ǿ���ͨ��int()����ת��������ת����int������ɲ���
	{
		return score;
	}
	studentRecord() {};
	studentRecord(string*name, int score) 
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



// ������������
//void binSort2(chain<studentRecord>& theChain, int range);




#endif // !__BIN_SORT_H__
#pragma once
