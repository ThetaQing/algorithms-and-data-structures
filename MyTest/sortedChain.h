// sorted chain, implements dictionary

#ifndef sortedChain_
#define sortedChain_

#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

using namespace std;
/*******************类说明*****************
* 类名：template<class K, class E> class sortedChain
* 类的说明：用链表实现的字典，继承自dictionary基类。主要的操作有：
			1、查找指定关键字的数对；
			2、插入数对；
			3、删除指定关键字的数对。
* 注意：从抽象类继承的类要实现基类（即该抽象类）的全部纯虚函数才能成为具体类，实现之前要在类中声明。

**/
template<class K, class E>
class sortedChain : public dictionary<K, E>
{
public:
	sortedChain() { firstNode = NULL; dSize = 0; }
	~sortedChain();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const pair<const K, E>&);
	void output(ostream& out) const;

protected:
	pairNode<K, E>* firstNode;  // 链表中指向第一个节点的指针
	int dSize;                 // 字典中所含数对的个数
};
/********************函数说明***********************
* 函数名：~sortedChain()
* 函数功能：sortedChain类的析构函数
* 函数实现：和链表的析构函数类似，字典的析构函数要删除字典中的所有节点

**/
template<class K, class E>
sortedChain<K, E>::~sortedChain()
{// 析构函数，删除字典内所有的节点
	while (firstNode != NULL)
	{// delete firstNode
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
/***************函数说明*********************
* 函数名：pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
* 函数参数：待查找数对的关键字
* 函数返回值：返回匹配的数对的指针，如果不存在匹配的数对，返回NULL

**/
template<class K, class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{// 返回匹配的数对的指针，如果不存在匹配的数对，返回NULL

	pairNode<K, E>* currentNode = firstNode;

	// 查找这个关键字
	while (currentNode != NULL &&
		currentNode->element.first != theKey)  // pair类通过first和second访问两个成员，在pairNode的定义中，first访问的成员是关键字
		currentNode = currentNode->next;

	// 如果匹配
	if (currentNode != NULL && currentNode->element.first == theKey)
		// 返回该数对
		return &currentNode->element;

	// 如果不匹配，返回NULL
	return NULL;
}
/*****************函数说明**************
* 函数名：void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
* 函数参数：要插入的数对
* 函数返回值：空
* 函数实现：
**/
template<class K, class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{// 将该数对插入到字典中，如果已经存在该关键字的数对，覆盖原来的数对

	pairNode<K, E>* p = firstNode,
		* tp = NULL; // tp指针在p指针的后面

// 移动指针tp，使thePair可以插在tp的后面，（字典按照关键字的递增顺序）
	while (p != NULL && p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}

	// 检查是否已经存在该关键字
	if (p != NULL && p->element.first == thePair.first)
	{// 如果已经存在该关键字，覆盖原来的值
		p->element.second = thePair.second;
		return;
	}

	// 如果是新数对，在字典中添加这个数对
	// 此时p指针指向的节点是新节点的下一个节点，而此时tp指针指向的节点的指针域指向p指针表示的节点，即
	// (tp)->(p)
	// （newNode）->(p)
	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);  // 字典节点的结构pairNode，第一个参数表示该字典节点，第二个参数表示指向下一个字典节点的指针

	// 将新加的数对加入到字典中，建立指针关系
	if (tp == NULL) firstNode = newNode;  // 如果字典是空的，新建的节点是首节点
	else tp->next = newNode;  // 否则把tp节点的指针域指向新节点

	dSize++;
	return;
}
/*******************函数说明*******************
* 函数名：void sortedChain<K, E>::erase(const K& theKey)
* 函数参数：待删除节点的关键字
* 函数返回值：空
* 函数功能：删除指定关键字的数对
**/
template<class K, class E>
void sortedChain<K, E>::erase(const K& theKey)
{//如果存在这个关键字的数对，删除这个数对
	pairNode<K, E>* p = firstNode,
		* tp = NULL; // tp trails p

// 查找这个关键字
	while (p != NULL && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}

	// 检查是否匹配
	if (p != NULL && p->element.first == theKey)
	{//如果有匹配的关键字，删除这个节点
		if (tp == NULL) firstNode = p->next;  // 如果该节点是首节点
		else tp->next = p->next;

		delete p;
		dSize--;
	}
}
/***************函数说明******************
* 函数名：void sortedChain<K, E>::output(ostream& out) const
* 函数参数：输出流
* 函数返回值：空

**/
template<class K, class E>
void sortedChain<K, E>::output(ostream& out) const
{// 将链表中的元素放入到输出流中
	for (pairNode<K, E>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}

// 重载 << 
template <class K, class E>
inline ostream& operator<<(ostream& out, const sortedChain<K, E>& x)
{
	x.output(out); return out;
}


// 其他函数声明
void testMainForSortedChain();


#endif