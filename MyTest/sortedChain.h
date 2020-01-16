// sorted chain, implements dictionary

#ifndef sortedChain_
#define sortedChain_

#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

using namespace std;
/*******************��˵��*****************
* ������template<class K, class E> class sortedChain
* ���˵����������ʵ�ֵ��ֵ䣬�̳���dictionary���ࡣ��Ҫ�Ĳ����У�
			1������ָ���ؼ��ֵ����ԣ�
			2���������ԣ�
			3��ɾ��ָ���ؼ��ֵ����ԡ�
* ע�⣺�ӳ�����̳е���Ҫʵ�ֻ��ࣨ���ó����ࣩ��ȫ�����麯�����ܳ�Ϊ�����࣬ʵ��֮ǰҪ������������

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
	pairNode<K, E>* firstNode;  // ������ָ���һ���ڵ��ָ��
	int dSize;                 // �ֵ����������Եĸ���
};
/********************����˵��***********************
* ��������~sortedChain()
* �������ܣ�sortedChain�����������
* ����ʵ�֣�������������������ƣ��ֵ����������Ҫɾ���ֵ��е����нڵ�

**/
template<class K, class E>
sortedChain<K, E>::~sortedChain()
{// ����������ɾ���ֵ������еĽڵ�
	while (firstNode != NULL)
	{// delete firstNode
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
/***************����˵��*********************
* ��������pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
* �������������������ԵĹؼ���
* ��������ֵ������ƥ������Ե�ָ�룬���������ƥ������ԣ�����NULL

**/
template<class K, class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{// ����ƥ������Ե�ָ�룬���������ƥ������ԣ�����NULL

	pairNode<K, E>* currentNode = firstNode;

	// ��������ؼ���
	while (currentNode != NULL &&
		currentNode->element.first != theKey)  // pair��ͨ��first��second����������Ա����pairNode�Ķ����У�first���ʵĳ�Ա�ǹؼ���
		currentNode = currentNode->next;

	// ���ƥ��
	if (currentNode != NULL && currentNode->element.first == theKey)
		// ���ظ�����
		return &currentNode->element;

	// �����ƥ�䣬����NULL
	return NULL;
}
/*****************����˵��**************
* ��������void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
* ����������Ҫ���������
* ��������ֵ����
* ����ʵ�֣�
**/
template<class K, class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{// �������Բ��뵽�ֵ��У�����Ѿ����ڸùؼ��ֵ����ԣ�����ԭ��������

	pairNode<K, E>* p = firstNode,
		* tp = NULL; // tpָ����pָ��ĺ���

// �ƶ�ָ��tp��ʹthePair���Բ���tp�ĺ��棬���ֵ䰴�չؼ��ֵĵ���˳��
	while (p != NULL && p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}

	// ����Ƿ��Ѿ����ڸùؼ���
	if (p != NULL && p->element.first == thePair.first)
	{// ����Ѿ����ڸùؼ��֣�����ԭ����ֵ
		p->element.second = thePair.second;
		return;
	}

	// ����������ԣ����ֵ�������������
	// ��ʱpָ��ָ��Ľڵ����½ڵ����һ���ڵ㣬����ʱtpָ��ָ��Ľڵ��ָ����ָ��pָ���ʾ�Ľڵ㣬��
	// (tp)->(p)
	// ��newNode��->(p)
	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);  // �ֵ�ڵ�ĽṹpairNode����һ��������ʾ���ֵ�ڵ㣬�ڶ���������ʾָ����һ���ֵ�ڵ��ָ��

	// ���¼ӵ����Լ��뵽�ֵ��У�����ָ���ϵ
	if (tp == NULL) firstNode = newNode;  // ����ֵ��ǿյģ��½��Ľڵ����׽ڵ�
	else tp->next = newNode;  // �����tp�ڵ��ָ����ָ���½ڵ�

	dSize++;
	return;
}
/*******************����˵��*******************
* ��������void sortedChain<K, E>::erase(const K& theKey)
* ������������ɾ���ڵ�Ĺؼ���
* ��������ֵ����
* �������ܣ�ɾ��ָ���ؼ��ֵ�����
**/
template<class K, class E>
void sortedChain<K, E>::erase(const K& theKey)
{//�����������ؼ��ֵ����ԣ�ɾ���������
	pairNode<K, E>* p = firstNode,
		* tp = NULL; // tp trails p

// ��������ؼ���
	while (p != NULL && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}

	// ����Ƿ�ƥ��
	if (p != NULL && p->element.first == theKey)
	{//�����ƥ��Ĺؼ��֣�ɾ������ڵ�
		if (tp == NULL) firstNode = p->next;  // ����ýڵ����׽ڵ�
		else tp->next = p->next;

		delete p;
		dSize--;
	}
}
/***************����˵��******************
* ��������void sortedChain<K, E>::output(ostream& out) const
* ���������������
* ��������ֵ����

**/
template<class K, class E>
void sortedChain<K, E>::output(ostream& out) const
{// �������е�Ԫ�ط��뵽�������
	for (pairNode<K, E>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}

// ���� << 
template <class K, class E>
inline ostream& operator<<(ostream& out, const sortedChain<K, E>& x)
{
	x.output(out); return out;
}


// ������������
void testMainForSortedChain();


#endif