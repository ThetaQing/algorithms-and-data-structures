#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__
// 线性表的抽象类
template<typename T>
class linearList
{
public:
	virtual ~linearList() {};  // 析构函数
	virtual bool empty() const = 0; // 当且仅当线性表为空时返回true，const表示这个函数内不能修改类的成员变量，除非那个成员变量时mutable的
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
// 从抽象类派生的类的要实现抽象类中所有的纯虚函数才能成为具体类，否则还是抽象类，不能建立对象或实例
template<typename T>
class chain : public linearList<T>
{
public:
	// 构造函数，复制构造函数和析构函数
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	// 抽象数据类型ADT的方法	
	
	// 当且仅当线性表为空时返回true，const表示这个函数内不能修改类的成员变量，除非那个成员变量时mutable的
	bool empty() const
	{
		return listSize == 0;
	}
	// 返回线性表的元素个数
	int size()const
	{
		return listSize;
	}
	// 返回索引为theIndex的元素
	T& get(int theIndex) const;
	

	 // 删除索引为theIndex的元素
	void erase(int theIndex);


	 // 把theElement插入线性表中索引为theIndex的位置上
	void insert(int theIndex, const T& theElement);


	 // 把线性表插入输出流out
	void output(ostream& out) const;



protected:
	void checkIndex(int theIndex) const;  // 如果索引无效，抛出异常
	chainNode<T>* firstNode;  // 指向链表第一个节点的指针，即指向线性表第0个元素的节点的指针
	int listSize; // 线性表的元素个数
};



/******************** 链表的构造函数和赋值构造函数***********************
* 函数名：
		构造函数：chain(int initialCapacity)
		复制构造函数：chain(const chain<T>& theList)

* 函数区别：
		构造函数：
				函数功能：创建一个新的空链表
				创建过程：只需令第一个节点指针firstNode的值为NULL。
				函数参数：一个e标识初始容量的形参initialCapacity
				时间复杂度：O(1)
		复制构造函数：
				函数功能：是一种特殊的构造函数，由编译器调用完成一些基于同一类的其他对象的构造及初始化。
				函数参数：形参必须是引用，一般会加上const限制
				创建过程：成员数据firstNode是指向形参theList的首元素指针；
						  定义一个targetNode表示当前在建链表的移动指针，最后是链表最后一个节点的尾指针；
						  定义一个sorceNode表示形参链表theList的移动指针，将形参链表中的节点逐个复制到在建链表。
				使用情景：1、一个对象作为函数参数，以值传递的方式传入函数体；
						  2、一个对象作为函数返回值，以值传递的方式从函数返回；
						  3、一个对象用于给另一个对象进行初始化（常称为赋值初始化）。
				时间复杂度：O(max{ListSize, theList.listSize})
						




**/

// 构造函数
template <typename T>
chain<T> ::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;  // 输出字符串流
		s << "Initial capacity = " << initialCapacity << "Must be > 0";
		throw illegalParameterValue(s.str());
	}
	firstNode = NULL;
	listSize = 0;

}

// 复制构造函数
template <typename T>
chain <T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;
	if (listSize == 0)
	{
		// 链表theList为空
		firstNode = NULL;
			return;
	}

	// 链表theList为非空
	chainNode<T>* sourceNode = theList.firstNode;  // 要复制链表theList的节点，所以sourceNode是新链表指向第一个节点的指针，并且这个节点就是链表theList中firstNode的拷贝
	firstNode = new chainNode<T>(sourceNode->element);  // 复制链表theList的首元素，类的成员数据，指向当前链表的第一个节点的指针
	sourceNode = sourceNode->next;  // 此时sourceNode指向了theList的第二个节点
	chainNode<T>* targetNode = firstNode;  // targetNode表示当前链表*this的最后一个节点，此时是指向第一个节点的
	while (sourceNode != NULL)  // 复制剩余元素
	{
		targetNode->next = new chainNode<T>(sourceNode->element);  // 第一次执行是拷贝theList的第二个节点，后面逐步向后移动
		targetNode = targetNode->next;  // 当前链表移动到下一个节点
		sourceNode = sourceNode->next;  // theList链表的下一个节点
	}
	targetNode->next = NULL;  // 链表结束
}

/***************析构函数************************
* 函数名：~chain()
* 函数功能：链表析构函数，删除链表的所有节点
* 函数使用：在销毁对象时自动执行，一个类只能有一个析构函数。

**/

template<typename T>
chain<T> ::~chain()
{
	while (firstNode != NULL)  // 删除首节点
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

/**************   get方法      *****************
* 函数名：
* 函数参数：int类型的索引theIndex
* 函数返回值：索引是theIndex的元素,若该元素不存在，抛出异常
* 函数实现：从第一个节点开始，跟踪链域next直到找到所需节点的位置
* 时间复杂度：O(theIndex)


*/

template<typename T>
T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);  // 检查该元素是否存在

	// 移向所需要的节点
	chainNode<T>* currentNode = firstNode;
	for (int i = 0l i < theIndex; ++i)
		currentNode = currentNode->next;
	return currentNode->element;
}





#endif


