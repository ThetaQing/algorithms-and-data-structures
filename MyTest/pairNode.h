#ifndef pairNode_
#define pairNode_

using namespace std;
// �����ֵ�����ݽṹ���ýṹ�а���һ����ʾ�ֵ�Ԫ�ص����ԣ�element����Ա��һ��ָ����һ���ֵ�ڵ��ָ��(theNext)
template <class K, class E>
struct pairNode
{
	typedef pair<const K, E> pairType;
	pairType element;
	pairNode<K, E>* next;

	pairNode(const pairType& thePair) :element(thePair) {}  // ���캯�����ð���ǳ�ʼ�����ʽ
	pairNode(const pairType& thePair, pairNode<K, E>* theNext)  
		:element(thePair) {
		next = theNext;
	}
};

#endif