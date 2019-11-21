#include <iostream>
#include "linear_list_apply.h"
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
**/
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
/************************************
=====================================

* 程序编号：6-19 数据结构 P140
* 程序功能：使用数组实现的并查集算法
* 全局变量：int* equivClass, n;   分别表示等价类数组和元素个数
* 说明：数组equivClass中equivClass[i]为包含元素i的等价类
* 时间复杂度：通常执行一次初始化、u次合并和f次查找，时间复杂度为O(n+u*n+f)
=====================================

**/


/******************函数说明**********************

* 函数名：void initialize(int numberOfElement)
* 函数参数：元素个数
* 函数返回值:空
* 函数功能：用每个类的一个元素，初始化numberOfElements个类
* 时间复杂度：O(n)


**/


void unionFindWithArray::initialize(int numberOfElement)
{
	n = numberOfElement;
	equivClass = new int[n + 1];
	for (int e = 1; e <= n; ++e)  // 类别是按非0自然数顺序排序
	{
		equivClass[e] = e;
	}
}

/*******************函数说明********************

* 函数名：void unite(int classA, int classB)
* 函数参数：两个不同的类classA和classB
* 函数返回值：空，全局指针返回两个类的unite计算结果
* 函数功能：合并类classA和classB，将classB的元素全部合并称为classA类
* 时间复杂度：O(n)

**/
void unionFindWithArray::unite(int classA, int classB)
{
	for (int k = 1; k <= n; ++k)  // 嘉禾classA ！= classB
	{
		if (equivClass[k] == classB)  // 找到所有classB中的元素，把这些元素全部合并到classA类中
			equivClass[k] = classA;
	}

}
/*******************函数说明********************

* 函数名：int find(int theElement)
* 函数参数：待查找元素
* 函数返回值：返回具有这个元素的类
* 函数功能：查找具有元素theElement的类
* 时间复杂度：O(1)
**/
int unionFindWithArray::find(int theElement)
{
	return equivClass[theElement];
}

/*******************函数说明*******************
* 函数名：void testUnionFindWithArrays(void)
* 函数参数：空
* 函数返回值：空
* 函数功能：对6-19程序进行测试

**/
void unionFindWithArray::testMain(void)
{
	initialize(10);
	unite(1, 2);  // 执行后1、2均为equivClass[1]类
	unite(3, 4);  // 执行后3、4均为equivClass[3]类
	unite(1, 3);  // 执行前，3、4均为equivClass[3]类，执行后，3、4均为equivClass[1]类。
	for (int i = 1; i < 10; ++i)
	{
		cout << "Element " << i << " is in equivalence class " << find(i) << endl;
	}
}

/**************************************************

===================================================

* 程序编号：6-20至6-21  P141
* 程序功能：用链表实现合并、查找
* 全局变量：equivNode* node;  // 节点的数组
			int n; // 元素个数

* 说明：程序6-20为结构体定义，类的定义同样见头文件linear_list_apply.h；数组索引表示类名，每个元素都是该元素作为索引的类的首元素
* 时间复杂度：通常执行一次初始化、u次合并和f次查找，时间复杂度为O(n+u*logu+f)

**/

/****************函数说明****************
* 函数名:initialize(int numberOfElement)
* 函数参数：类的个数；注意，不同类的名字由1--numberOfElement自然数进行区别
* 函数返回值：空
* 函数功能：初始化numberOfElement个类，每个类的名字按照1--numberOfElement自然数进行区别
* 时间复杂度：O(n)

**/
// 用每个类的一个元素，初始化numberOfElement个类
void unionFindWithChains::initialize(int numberOfElement)
{
	n = numberOfElement;
	node = new equivNode[n + 1];  // node是一个数组，数组元素是一个链表，链表的节点是一个结构体
	for (int e = 1; e <= n; ++e)  // 每一个节点都是一个链表
	{
		node[e].equivClass = e;
		node[e].next = 0;  // 链表中没有下一个节点
		node[e].size = 1;
	}
}
/****************函数说明****************
* 函数名:unite(int classA, int classB)
* 函数参数：两个不同的类，且都是链表的首元素！！！
* 函数返回值：空
* 函数功能：将小的类合并到大的类中
* 时间复杂度：u次合并操作所需要的时间为O(ulogu)
* 其他说明：1、合并之前，如果classA中的元素个数小于或等于classB的，那么将A类合并到B类，此时classB是链表首元素；反之A类是链表首元素
			2、合并之后，只有链表首元素表示的类size发生了变化，其他类的size都没有发生变化
**/

// 合并类ClassA和classB
void unionFindWithChains::unite(int classA, int classB)
{
	//假设classA和classB不相等，并且都是链表首元素

	//使classA称为较小的类
	if (node[classA].size > node[classB].size)
		swap(classA, classB);
	// 改变较小类的equivClass

	int k;
	for (k = classA; node[k].next != 0; k = node[k].next)
		node[k].equivClass = classB;  // 把A类中的所有节点全部划分到B类中
	node[k].equivClass = classB;		// 链表的最后一个节点

	// 在链表classB的首元素之后插入链表classA
	// 修改新链表的大小
	node[classB].size += node[classA].size;
	node[k].next = node[classB].next;  // 要在classB的首元素后面插入classA，就要先保留classB首元素的下一个元素，即先用新插入的链表指向首元素的下一个元素
	node[classB].next = classA;  // 再把新链表的首元素作为首元素的下一个元素

}
/****************函数说明****************
* 函数名:find(int theElement)
* 函数参数：待查找的元素
* 函数返回值：返回包含该元素的类名
* 函数功能：寻找包含元素theElement的类
* 时间复杂度：O(1)

**/
// 查找包含元素theElement的类
int unionFindWithChains::find(int theElement)
{
	return node[theElement].equivClass;
}

void unionFindWithChains::testMain()
{
	initialize(7);
	unite(1, 2);
	unite(3, 4);
	unite(4, 5);
	unite(2, 5);

	for (int i = 1; i <= 7; ++i)
		cout << "包含"<< i << "元素的类是" << find(i) << endl;
}
