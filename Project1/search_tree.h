#ifndef __SEARCH_TREE_H__
#define __SEARCH_TREE_H__

// C++抽象类 bsTree，二叉搜索树
template <typename K, typename E>
class binarySearchTree : public dictionary<K, E>  // dictionary P237
{
public:
	virtual void ascend() = 0;  // 按关键字升序输出
	pair<const K, E>* find(const K& theKey);
};


// C++抽象类 indexedBSTree 索引二叉搜索树
template <typename K, typename E>
class indexedBSTree : public binarySearchTree<K, E>
{
public:
	virtual pair <const K, E>* get(int) const = 0;  
	// 根据给定的索引，返回其数对的指针
	virtual void delete(int) = 0;
	// 根据给定的索引，删除其数对
};

#endif 
