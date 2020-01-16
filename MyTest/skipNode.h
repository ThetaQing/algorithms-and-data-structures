#ifndef skipNode_
#define skipNode_

template <class K, class E>
struct skipNode
{
	typedef pair<const K, E> pairType;
	pairType element;
	skipNode<K, E>** next;   // ָ����next[i]��ʾi������ָ��

	skipNode(const pairType& thePair, int size)  // ���캯�������ֵ����Դ���element��Ϊָ���������ռ䣬��һ��lev���������ԣ���sizeֵӦΪlev+1.
		:element(thePair) {
		next = new skipNode<K, E> * [size];
	}
};

#endif
