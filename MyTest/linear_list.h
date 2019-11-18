#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__
#include <iostream>
#include <sstream>

using namespace std;
// 其他函数声明
void testBinSort();


// 线性表的抽象类
template<typename T>
class linearList
{
public:
	virtual ~linearList() {};  // 析构函数
	virtual bool empty() const = 0; // 当且仅当线性表为空时返回true，const表示这个函数内不能修改类的成员变量，除非那个成员变量时mutable的
	virtual int size()const = 0;  // 返回线性表的元素个数
	virtual T& get(int theIndex) const = 0;  // 返回索引为theIndex的元素
	virtual int indexOf(const T& theElement) const = 0;  // 返回元素theElement第一次出现时的索引
	virtual void erase(int theIndex) = 0;  // 删除索引为theIndex的元素
	virtual void insert(int theIndex, const T& theElement) = 0;  // 把theElement插入线性表中索引为theIndex的位置上
	virtual void output(ostream& out) const = 0;  // 吧线性表插入输出流out
};

// 链表节点的结构定义
/**************结构说明*************
* 结构名： chainNode
* 结构功能：一个链表的节点，包含两个部分，一个数据域，一个指针域，指针域的指针指向下一个节点
* 构造函数说明：
		1、默认构造函数：构造一个空节点；
		2、带数据域的构造函数：构造一个节点，该节点的数据域的数值是形参element
		3、带节点构造函数:构造一个节点，该节点的数据域是形参element，指针域的指针即为形参指针（即两个指针指向同一个节点）

**/
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
	chainNode(const T& element, chainNode<T>* next)  // 构造一个节点，这个节点的指针域的指针是指向形参next指向的节点（）也就是next表示的这个节点,简单来说就是形参next就是这个节点的指针
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
	
	// 返回元素theElement第一次出现时的索引
	int indexOf(const T& theElement)const;

	 // 删除索引为theIndex的元素
	void erase(int theIndex);


	 // 把theElement插入线性表中索引为theIndex的位置上
	void insert(int theIndex, const T& theElement);


	 // 把线性表插入输出流out
	void output(ostream& out) const;

	// 新增函数
	void clear();  // 清表
	void binSort(int range);  // 箱子排序


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
		throw s.str();//illegalParameterValue(s.str());
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
	for (int i = 0; i < theIndex; ++i)
		currentNode = currentNode->next;
	return currentNode->element;
}


/**************函数说明***************
* 函数名：indexOf(const T& theElement)const
* 函数参数：一个与链表中元素类型相同的元素值
* 函数返回值: 返回元素theElement首次出现的索引,若不存在，返回-1
* 时间复杂度：O(listSize)



**/

template<typename T>
int chain<T>::indexOf(const T& theElement)const
{
	// 搜索链表寻找元素theElement
	chainNode<T>* currentNode = firstNode;
	int index = 0; // 当前节点的索引
	while (currentNode != NULL && currentNode->element != theElement)
	{ 
		// 移向下一个节点
		currentNode = currentNode->next;
		index += 1;
	}
	// 确认是否找到所需元素
	if (currentNode == NULL)  // 退出循环如果是到了末尾还没有找到，说明该元素不在链表中，返回-1
		return -1;
	else
		return index;


}

/***************函数说明**********************
* 函数名：erase(int theIndex)
* 函数参数：int类型，要删除节点的索引
* 函数返回值：空
* 函数功能：删除索引为theIndex的元素
* 相关说明：主要考虑三个细节：
				1、索引无效；
				2、删除非空链表的第0个元素节点，最后的元素节点；
				3、删除其他元素节点;
				4、删除节点之后链表的大小要相应发生变化
* 时间复杂度：O(theIndex)

**/
template <typename T>
void chain<T>::erase(int theIndex)
{
	// 检查索引是否有效,若无效，抛出异常
	checkIndex(theIndex);  

	// 若索引有效，删除该节点
	chainNode<T>* deleteNode;
	if (theIndex == 0)  // 删除头结点
	{
		deleteNode =  firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* p = firstNode;  // 用指针p指向要删除节点的前驱节点
		
		for (int index = 1; index != theIndex; ++index)  // 当退出循环后，p指向要删除节点的前驱节点
		{
			p = p->next;  
			
		}
		deleteNode = p->next;  
		p->next = deleteNode->next;  // 删除deleteNode指向的节点，即将删除节点的前驱节点指针域指针指向删除节点后继节点
	}
	listSize -= 1;
	delete deleteNode;

}
/*****************函数说明***********************
* 函数名：insert(int theIndex, const T& theElement)
* 函数参数：插入节点的未来索引，节点的数值
* 函数返回值：
* 时间复杂度：O(theIndex)



**/
template <typename T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	if (theIndex == 0)  // 在表头插入
	{
		firstNode = new chainNode<T>(theElement, firstNode);  // new返回的是地址
	}
	else
	{
		chainNode<T>* p = firstNode;  // 定义一个节点指针p，表示插入位置的前驱节点
		// 寻找位置
		for (int index = 1; index < theIndex; ++index)  // index=1的时候指向第0个节点，index=2的时候指向第1个节点
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);  // 新建这个插入的节点		

	}
	listSize += 1;
}
/****************函数说明***********************
* 函数名：checkIndex(int theIndex)const
* 函数参数：int 类型索引
* 函数返回值：空，若索引无效，抛出异常




**/
template <typename T>
void chain<T>::checkIndex(int theIndex)const
{
	if (theIndex < 0 || theIndex > listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw s.str();
	}
}




/******************函数说明******************
* 函数名：output(ostream& out)const
* 函数参数：输出流对象
* 函数返回值：无
* 实现功能：将链表放入输出流中
* 时间复杂度：O(listSize)



**/

template <typename T>
void chain<T>::output(ostream& out)const
{
	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		
		out << currentNode->element << "  ";
	}
}
/******************函数说明**********************
* 函数名：operator<<(ostream& out, const chain<T>& x)
* 函数参数：输出流对象，链表
* 函数返回值：输出流对象
* 其他说明：重载 <<
		重载的运算符是带有特殊名称的函数，函数名是由关键字operator和其后要重载的运算符符号构成，有一个返回类型和一个参数列表。
**/
template <typename T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}

/********************函数说明*********************
* 函数名：clear()
* 函数参数：无
* 函数返回值：无
* 函数功能：清空链表，删除链表的所有节点


**/

template <typename T>
void chain<T> ::clear()
{
	
	while (firstNode->next != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;  // 一定要指向要删除节点的下一个节点，否则删除这个节点之后，这个节点的指针域就没有意义了，找不到下一个节点
		delete firstNode;
		firstNode = nextNode;
	}
	listSize = 0;
}
/***************函数说明**********************
* 函数名：
* 函数参数：
* 函数返回值：
* 其他说明：每个箱子都以底部节点作为首节点，顶部节点作为尾结点。每个箱子都有两个指针，分别存储在数组bottom和top中；
			分别指向尾结点和有节点。bottom[theBin]指向箱子theBin的尾结点，而top[theBin]指向箱子theBin的首节点。所有箱子开始为空表，
			此时bottom[theBin]=NULL

**/
template <typename T>
void chain<T>::binSort(int range)
{
	// 对链表中的节点排序
	// 创建并初始化箱子
	chainNode<T>** bottom, ** top;  // 跟踪首尾节点
	int len = range + 1;
	bottom = new chainNode<T>* [len];  // 指向节点指针的指针
	top = new chainNode<T>* [len];  // 指向节点指针的指针
	for (int b = 0; b <= range; ++b)
	{
		bottom[b] = NULL;
	}
	// 把链表的节点分配给箱子
	for (; firstNode != NULL;firstNode = firstNode->next)
	{
		// 把首节点加到箱子中
		int theBin = firstNode->element;  // 元素类型转换到整型,变成索引
		if (bottom[theBin] == NULL)  // 箱子为空
			bottom[theBin] = top[theBin] = firstNode;
		else  // 箱子不为空
		{
			top[theBin]->next = firstNode;
			top[theBin] = firstNode;  // ????
		}
	}

	// 把箱子中的节点收集到有序链表
	chainNode<T>* y = NULL;
	for (int theBin = 0; theBin <= range; ++theBin)
	{
		if (bottom[theBin] != NULL) // 箱子不为空
		{
			if (y == NULL)  // 第一个箱子非空
				firstNode = bottom[theBin];
			else
				y->next = bottom[theBin];  // 不是第一个非空箱子
			y = top[theBin];
		}


	}
	if (y != NULL)
		y->next = NULL;
	   	  
	delete[] top;
	delete[] bottom;

}




#endif


