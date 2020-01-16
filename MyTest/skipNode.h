#ifndef skipNode_
#define skipNode_

template <class K, class E>
struct skipNode
{
	typedef pair<const K, E> pairType;
	pairType element;
	skipNode<K, E>** next;   // 指针域，next[i]表示i级链表指针

	skipNode(const pairType& thePair, int size)  // 构造函数，把字典数对存入element域，为指针数组分配空间，对一个lev级链表数对，其size值应为lev+1.
		:element(thePair) {
		next = new skipNode<K, E> * [size];
	}
};

#endif
