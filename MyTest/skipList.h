// skip list data structure, implements dictionary

#ifndef skipList_
#define skipList_



#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include "dictionary.h"
#include "skipNode.h"
#include "myExceptions.h"

using namespace std;

template<class K, class E>
class skipList : public dictionary<K, E>
{
public:
	skipList(K, int maxPairs = 10000, float prob = 0.5);
	~skipList();
	// 基类的纯虚函数
	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const pair<const K, E>&);
	void output(ostream& out) const;

protected:
	float cutOff;          // 用来确定层数
	int level() const;     // 级的分配方法
	int levels;            // 当前最大的非空链表
	int dSize;             // 字典的数对个数
	int maxLevel;          // 允许的最大链表层数
	K tailKey;             // 最大关键字
	skipNode<K, E>* search(const K&) const;
	// 搜索函数
	skipNode<K, E>* headerNode;  // 头节点指针
	skipNode<K, E>* tailNode;    //  尾结点指针
	skipNode<K, E>** last;       // last[i]表示i层的最后节点
};

template<class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{// 构造函数，关键字小于largeKey且数对个数size最多为maxPairs。0 < prob < 1.
	cutOff = prob * RAND_MAX;
	maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;  // 初始化层数
	dSize = 0;
	tailKey = largeKey;

	// 生成头节点、尾结点和数组last
	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E> * [maxLevel + 1];

	// 链表为空时，任意级链表中的头节点都指向尾结点
	for (int i = 0; i <= maxLevel; i++)
		headerNode->next[i] = tailNode;
}

template<class K, class E>
skipList<K, E>::~skipList()
{// 析构函数，删除所有节点
	skipNode<K, E>* nextNode;

	// 删除所有节点
	while (headerNode != tailNode)
	{
		nextNode = headerNode->next[0];
		delete headerNode;
		headerNode = nextNode;
	}
	delete tailNode;

	delete[] last;
}

template<class K, class E>
pair<const K, E>* skipList<K, E>::find(const K& theKey) const
{// 返回匹配的数对的指针
 // 如果没有匹配的数对，返回NULL
	if (theKey >= tailKey)
		return NULL;  // 没有可能的匹配的数对

	 // 位置beforeNode是关键字为theKey的节点之前最右边的位置
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)          // 从上级链表到下级链表
	   // 跟踪i级链表指针
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];

	// 检查下一个节点的关键字是否是theKey
	if (beforeNode->next[0]->element.first == theKey)
		return &beforeNode->next[0]->element;

	return NULL;  // 没有匹配的数对
}

template<class K, class E>
int skipList<K, E>::level() const
{// Return a random level number <= maxLevel.
	int lev = 0;
	while (rand() <= cutOff)
		lev++;
	return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{// Search for theKey saving last nodes seen at each
 // level in the array last
 // Return node that might contain theKey.
   // position beforeNode just before possible node with theKey
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;  // last level i node seen
	}
	return beforeNode->next[0];
}

template<class K, class E>
void skipList<K, E>::insert(const pair<const K, E>& thePair)
{// Insert thePair into the dictionary. Overwrite existing
 // pair, if any, with same key.
	if (thePair.first >= tailKey) // key too large
	{
		ostringstream s;
		s << "Key = " << thePair.first << " Must be < " << tailKey;
		throw illegalParameterValue(s.str());
	}

	// see if pair with theKey already present
	skipNode<K, E>* theNode = search(thePair.first);
	if (theNode->element.first == thePair.first)
	{// update theNode->element.second
		theNode->element.second = thePair.second;
		return;
	}

	// not present, determine level for new node
	int theLevel = level(); // level of new node
	// fix theLevel to be <= levels + 1
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}

	// get and insert new node just after theNode
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{// insert into level i chain
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}

	dSize++;
	return;
}

template<class K, class E>
void skipList<K, E>::erase(const K& theKey)
{// Delete the pair, if any, whose key equals theKey.
	if (theKey >= tailKey) // too large
		return;

	// see if matching pair present
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey) // not present
		return;

	// delete node from skip list
	for (int i = 0; i <= levels &&
		last[i]->next[i] == theNode; i++)
		last[i]->next[i] = theNode->next[i];

	// update levels
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;

	delete theNode;
	dSize--;
}

template<class K, class E>
void skipList<K, E>::output(ostream& out) const
{// Insert the dictionary pairs into the stream out.
   // follow level 0 chain
	for (skipNode<K, E>* currentNode = headerNode->next[0];
		currentNode != tailNode;
		currentNode = currentNode->next[0])
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}

// overload <<
template <class K, class E>
ostream& operator<<(ostream& out, const skipList<K, E>& x)
{
	x.output(out); return out;
}

#endif