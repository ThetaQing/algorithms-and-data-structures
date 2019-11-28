#include <iostream>
#include "linear_list.h"
#include "linear_list_apply.h"
using namespace std;


/****************文件说明*****************
* 文件名：linear_list.cpp
* 数据类型：线性表：也称有序表，它的每一个实例都是元素的一个有序集合。
* 文件功能：实现 第五、六章 线性表
* 主要知识点：
	1、抽象类：包含有纯虚函数的类，抽象类是用来做基类的，不能被实例化或建立对象，而且要将虚构函数定义为虚函数。
	2、链：也称指针，每一个节点都明确包含另一个相关节点的位置信息。


**/

void testBinSort()
{
	chain<studentRecord> the_chain;
	
	string A, B, C;
	A = "A";
	B = "B";
	C = "C";
	studentRecord student1{ &A, 3 }, student2{ &B,1 }, student3{&C, 2};  // 定义数据
	
	

	the_chain.insert(0, student1);
	the_chain.insert(0, student2);
	the_chain.insert(0, student3);
	
	cout << "  " << the_chain << endl;
	the_chain.binSort(4);  // 参数是输入数的最大值
	cout << "  " << the_chain<< endl;
	
}
