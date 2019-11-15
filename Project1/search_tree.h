#ifndef __SEARCH_TREE_H__
#define __SEARCH_TREE_H__

// C++������ bsTree������������
template <typename K, typename E>
class binarySearchTree : public dictionary<K, E>  // dictionary P237
{
public:
	virtual void ascend() = 0;  // ���ؼ����������
	pair<const K, E>* find(const K& theKey);
};


// C++������ indexedBSTree ��������������
template <typename K, typename E>
class indexedBSTree : public binarySearchTree<K, E>
{
public:
	virtual pair <const K, E>* get(int) const = 0;  
	// ���ݸ��������������������Ե�ָ��
	virtual void delete(int) = 0;
	// ���ݸ�����������ɾ��������
};

#endif 
