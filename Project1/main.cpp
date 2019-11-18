#include "sort.h"
#include <iostream>
#include "algostuff.hpp"
#include"linear_list.h"
#include "bin_sort.h"
using namespace std;
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
}

int main()
{
	chain<studentRecord> the_chain;

	string A, B, C;
	A = "A";
	B = "B";
	C = "C";
	studentRecord student1{ &A, 3 }, student2{ &B,1 }, student3{ &C, 2 };

	chain<studentRecord> *new_chain = new chain<studentRecord>;
	new_chain->insert(0, student1);
	new_chain->insert(0, student1);
	new_chain->insert(0, student2);
	new_chain->insert(0, student3);

	the_chain.insert(0, student1);
	the_chain.insert(0, student2);
	the_chain.insert(0, student3);
	cout << "   " << *new_chain << endl;

	binSort2(*new_chain, 4);
	cout << "   " << *new_chain << endl;
	/*
	int a = 0;
	int* p = &a;
	vector <int> vec{ 1,2,4,3,2 };
	int array[10] = { 8, 1, 14, 3, 21, 5, 7, 10, 45, -11 };
	
	for (auto it : vec)
	{
		cout << it << endl;
	}
	*/
	delete new_chain;
	system("pause");
	return 0;
}


