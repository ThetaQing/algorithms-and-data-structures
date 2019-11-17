#ifndef __BIN_SORT_H__
#define __BIN_SORT_H__
#include <iostream>
using namespace std;
/*************文件说明****************
* 文件名：bin_sort.h
* 文件功能：实现箱子排序
* 主要步骤：
		1、逐个删除输入链表的节点，把删除的节点分配到相应的箱子里；
		2、把每一个箱子中的链表收集并链接起来，使其成为一个有序链表。

**/

struct studentRecord
{
	int score;
	std::string* name;
	int operator != (const studentRecord& x)const  // 重载运算符 ！=,它把studentRecord类型转换为数值类型，以实现比较操作和其他目的
	{
		return (score != x.score);
	}	
	operator int() const  // 重载类型转换操作符int()，其他算术和关系操作符虽然没有重载或明确定义，但是可以通过int()类型转换操作符转换成int类型完成操作
	{
		return score;
	}
};

std::ostream& operator<<(ostream& out, const studentRecord& x)  // 重载运算符 <<
{
	out << x.score << " " << *x.name << endl;
	return out;

}









#endif // !__BIN_SORT_H__
#pragma once
