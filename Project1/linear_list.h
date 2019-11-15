#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__
// 线性表的抽象类
template<typename T>
class linearList
{
public:
	virtual ~linearList() {};  // 析构函数
	virtual bool empty() const = 0; // 当且仅当线性表为空时返回true
	virtual int size()const = 0;  // 返回线性表的元素个数
	virtual T& get(int theIndex) const = 0;  // 返回索引为theIndex的元素
	virtual void erase(int theIndex) = 0;  // 删除索引为theIndex的元素
	virtual void insert(int theIndex, const T& theElement) = 0;  // 把theElement插入线性表中索引为theIndex的位置上
	virtual void output(ostream& out) const = 0;  // 吧线性表插入输出流out
};

// 链表节点的结构定义
template <typename T>
struct chainNode
{
	// 数据成员
	T element;  // 数据
	chainNode<T>* next;  // 该节点的指针域，一个指向下一个节点的指针

	// 方法
	chainNode() {}  // 无参数的构造函数
	chainNode(const T& element)  // 有参数的构造函数
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;  // this->element访问的是实例中的数据成员
		this->next = next;
	}
};


// 链表的类定义

template<typename T>
class chain : public linearList<T>
{
public:
	// 构造函数，复制构造函数和析构函数
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	// 抽象数据类型ADT的方法

};

#endif // !__LINEAR_LIST_H__

