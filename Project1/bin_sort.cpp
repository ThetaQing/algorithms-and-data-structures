#include <iostream>
#include "bin_sort.h"
#include "linear_list.h"
using namespace std;
/***********文件说明************
* 文件名：bin_sort.cpp（箱子排序）
* 文件功能：实现箱子排序，对学生成绩从小到大排序

**/

/****************函数说明************************
* 函数名： void binSort(chain<studentRecord>& theChain, int range)
* 函数参数：一个记录学生成绩的链表，成绩输入范围
* 函数返回值：地址传递，从小到大排序的学生成绩链表
* 函数功能：使用链表的多个方法进行箱子排序
* 实现步骤：
		1、连续删除链表的首元素，并将其插入插入相应的某个箱子的链表首位；
		2、从最后一个箱子开始（按照从小到大排序），逐个删除每个箱子的元素，并将其插入一个初始为空的链表的首位
* 时间复杂度：如果不考虑内存分配异常的话，第一个for循环O(n)，第二个for循环O(range)，总的时间复杂度O(n+range)

void binSort2(chain<studentRecord>& theChain, int range)
{
	// 按分数排序

	// 对箱子初始化
	chain<studentRecord>* bin;
	bin = new chain<studentRecord>[range + 1];  // 每一个箱子用一个链表表示

	// 把学生记录从链表中取出，然后分配到箱子里
	int numberOfElements = theChain.size();
	for (int i = 1; i <= numberOfElements; ++i)
	{
		studentRecord x = theChain.get(0);  // 这个方法妙极了，这样的话get、insert、erase操作都只需要O(1)的时间
		theChain.erase(0);
		bin[x.score].insert(0, x);  // 箱子是一个链表结构
	}

	// 从箱子中收集元素
	for (int j = range; j >= 0; --j)  // 从最后一个箱子开始，从小到大的顺序
	{
		while (!bin[j].empty())  // 清空这个箱子
		{
			studentRecord x = bin[j].get(0);
			bin[j].erase(0);
			theChain.insert(0, x);  // 类似于栈，一直从表头压入，最大的在最后
		}
	}
	delete[] bin;  // 释放内存
}**/


