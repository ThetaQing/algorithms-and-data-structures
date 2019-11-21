#ifndef __BIN_SORT_H__
#define __BIN_SORT_H__
#include <string>
#include "linear_list.h"
using namespace std;
/*************文件说明****************
* 文件名：bin_sort.h
* 文件功能：实现箱子排序
* 主要步骤：
		1、逐个删除输入链表的节点，把删除的节点分配到相应的箱子里；
		2、把每一个箱子中的链表收集并链接起来，使其成为一个有序链表。

**/

// 结构体定义
struct studentRecord
{
	int score;
	std::string* name;
	/*
	int operator != (const studentRecord& x)const  // 重载运算符 ！=,它把studentRecord类型转换为数值类型，以实现比较操作和其他目的
	{
		return (score != x.score);
	}
	*/	
	operator int() const  // 重载类型转换操作符int()，其他算术和关系操作符虽然没有重载或明确定义，但是可以通过int()类型转换操作符转换成int类型完成操作
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

/*************函数说明****************

* 函数名：
* 函数参数：
* 函数返回值：
* 函数功能：重载运算符<<
ostream& operator<<(ostream& out, const studentRecord& x)  // 重载运算符 <<
{
	out << x.score << ' ' << *x.name << endl;
	return out;

}*/

/****************************************
==========================================
* 类名：unionFindWithArray
* 类功能：数组实现合并集的合并、查找
* 类的成员：
	void initialize(int numberOfElement);  // 初始化函数
	void unite(int classA, int classB);  // 合并函数

	int find(int theElement); // 查找函数
	void testMain();  // 测试函数

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
	int* equivClass, n;  // 分别表示等价类数组和元素个数
};


// 其他函数声明
void binSort2(chain<studentRecord>& theChain, int range);
void testUnionFindWithArrays(void);
// 链表节点的结构体声明
struct  equivNode
{
	int equivClass;  // 元素类标识符
	int size; // 类的元素个数
	int next;  // 类中指向下一个元素的指针
};
/****************************************
==========================================
* 类名：unionFindWithChains
* 类功能： 链表实现合并集的合并、查找
* 类的成员：
	void initialize(int numberOfElement);  // 初始化函数
	void unite(int classA, int classB);  // 合并函数
	 
	int find(int theElement); // 查找函数
	void testMain();  // 测试函数

==========================================
*/

class unionFindWithChains
{
public:
	void initialize(int numberOfElement);  // 初始化函数
	void unite(int classA, int classB);  // 合并函数
	 
	int find(int theElement); // 查找函数
	void testMain();  // 测试函数

private:
	equivNode* node;  // 节点的数组
	int n; // 元素个数
};
#endif // !__BIN_SORT_H__
#pragma once
