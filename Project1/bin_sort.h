#ifndef __BIN_SORT_H__
#define __BIN_SORT_H__
#include <iostream>
using namespace std;
/*************�ļ�˵��****************
* �ļ�����bin_sort.h
* �ļ����ܣ�ʵ����������
* ��Ҫ���裺
		1�����ɾ����������Ľڵ㣬��ɾ���Ľڵ���䵽��Ӧ�������
		2����ÿһ�������е������ռ�������������ʹ���Ϊһ����������

**/

struct studentRecord
{
	int score;
	std::string* name;
	int operator != (const studentRecord& x)const  // ��������� ��=,����studentRecord����ת��Ϊ��ֵ���ͣ���ʵ�ֱȽϲ���������Ŀ��
	{
		return (score != x.score);
	}	
	operator int() const  // ��������ת��������int()�����������͹�ϵ��������Ȼû�����ػ���ȷ���壬���ǿ���ͨ��int()����ת��������ת����int������ɲ���
	{
		return score;
	}
};

std::ostream& operator<<(ostream& out, const studentRecord& x)  // ��������� <<
{
	out << x.score << " " << *x.name << endl;
	return out;

}









#endif // !__BIN_SORT_H__
#pragma once
