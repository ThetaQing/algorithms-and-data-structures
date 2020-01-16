#ifndef pairNode_
#define pairNode_

using namespace std;
// 定义字典的数据结构，该结构中包含一个表示字典元素的数对（element）成员和一个指向下一个字典节点的指针(theNext)
template <class K, class E>
struct pairNode
{
	typedef pair<const K, E> pairType;
	pairType element;
	pairNode<K, E>* next;

	pairNode(const pairType& thePair) :element(thePair) {}  // 构造函数后加冒号是初始化表达式
	pairNode(const pairType& thePair, pairNode<K, E>* theNext)  
		:element(thePair) {
		next = theNext;
	}
};

#endif