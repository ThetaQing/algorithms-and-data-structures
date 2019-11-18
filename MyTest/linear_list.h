#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__
#include <iostream>
#include <sstream>

using namespace std;
// ������������
void testBinSort();


// ���Ա�ĳ�����
template<typename T>
class linearList
{
public:
	virtual ~linearList() {};  // ��������
	virtual bool empty() const = 0; // ���ҽ������Ա�Ϊ��ʱ����true��const��ʾ��������ڲ����޸���ĳ�Ա�����������Ǹ���Ա����ʱmutable��
	virtual int size()const = 0;  // �������Ա��Ԫ�ظ���
	virtual T& get(int theIndex) const = 0;  // ��������ΪtheIndex��Ԫ��
	virtual int indexOf(const T& theElement) const = 0;  // ����Ԫ��theElement��һ�γ���ʱ������
	virtual void erase(int theIndex) = 0;  // ɾ������ΪtheIndex��Ԫ��
	virtual void insert(int theIndex, const T& theElement) = 0;  // ��theElement�������Ա�������ΪtheIndex��λ����
	virtual void output(ostream& out) const = 0;  // �����Ա���������out
};

// ����ڵ�Ľṹ����
/**************�ṹ˵��*************
* �ṹ���� chainNode
* �ṹ���ܣ�һ������Ľڵ㣬�����������֣�һ��������һ��ָ����ָ�����ָ��ָ����һ���ڵ�
* ���캯��˵����
		1��Ĭ�Ϲ��캯��������һ���սڵ㣻
		2����������Ĺ��캯��������һ���ڵ㣬�ýڵ�����������ֵ���β�element
		3�����ڵ㹹�캯��:����һ���ڵ㣬�ýڵ�����������β�element��ָ�����ָ�뼴Ϊ�β�ָ�루������ָ��ָ��ͬһ���ڵ㣩

**/
template <typename T>
struct chainNode
{
	// ���ݳ�Ա
	T element;  // ����
	chainNode<T>* next;  // �ýڵ��ָ����һ��ָ����һ���ڵ��ָ��

	// ����
	chainNode() {}  // �޲����Ĺ��캯��
	chainNode(const T& element)  // �в����Ĺ��캯��
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next)  // ����һ���ڵ㣬����ڵ��ָ�����ָ����ָ���β�nextָ��Ľڵ㣨��Ҳ����next��ʾ������ڵ�,����˵�����β�next��������ڵ��ָ��
	{
		this->element = element;  // this->element���ʵ���ʵ���е����ݳ�Ա
		this->next = next;  
	}
};


// ������ඨ��
// �ӳ��������������Ҫʵ�ֳ����������еĴ��麯�����ܳ�Ϊ�����࣬�����ǳ����࣬���ܽ��������ʵ��
template<typename T>
class chain : public linearList<T>
{
public:
	// ���캯�������ƹ��캯������������
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	// ������������ADT�ķ���	
	
	// ���ҽ������Ա�Ϊ��ʱ����true��const��ʾ��������ڲ����޸���ĳ�Ա�����������Ǹ���Ա����ʱmutable��
	bool empty() const
	{
		return listSize == 0;
	}
	// �������Ա��Ԫ�ظ���
	int size()const
	{
		return listSize;
	}
	// ��������ΪtheIndex��Ԫ��
	T& get(int theIndex) const;
	
	// ����Ԫ��theElement��һ�γ���ʱ������
	int indexOf(const T& theElement)const;

	 // ɾ������ΪtheIndex��Ԫ��
	void erase(int theIndex);


	 // ��theElement�������Ա�������ΪtheIndex��λ����
	void insert(int theIndex, const T& theElement);


	 // �����Ա���������out
	void output(ostream& out) const;

	// ��������
	void clear();  // ���
	void binSort(int range);  // ��������


protected:
	void checkIndex(int theIndex) const;  // ���������Ч���׳��쳣
	chainNode<T>* firstNode;  // ָ�������һ���ڵ��ָ�룬��ָ�����Ա��0��Ԫ�صĽڵ��ָ��
	int listSize; // ���Ա��Ԫ�ظ���
};



/******************** ����Ĺ��캯���͸�ֵ���캯��***********************
* ��������
		���캯����chain(int initialCapacity)
		���ƹ��캯����chain(const chain<T>& theList)

* ��������
		���캯����
				�������ܣ�����һ���µĿ�����
				�������̣�ֻ�����һ���ڵ�ָ��firstNode��ֵΪNULL��
				����������һ��e��ʶ��ʼ�������β�initialCapacity
				ʱ�临�Ӷȣ�O(1)
		���ƹ��캯����
				�������ܣ���һ������Ĺ��캯�����ɱ������������һЩ����ͬһ�����������Ĺ��켰��ʼ����
				�����������βα��������ã�һ������const����
				�������̣���Ա����firstNode��ָ���β�theList����Ԫ��ָ�룻
						  ����һ��targetNode��ʾ��ǰ�ڽ�������ƶ�ָ�룬������������һ���ڵ��βָ�룻
						  ����һ��sorceNode��ʾ�β�����theList���ƶ�ָ�룬���β������еĽڵ�������Ƶ��ڽ�����
				ʹ���龰��1��һ��������Ϊ������������ֵ���ݵķ�ʽ���뺯���壻
						  2��һ��������Ϊ��������ֵ����ֵ���ݵķ�ʽ�Ӻ������أ�
						  3��һ���������ڸ���һ��������г�ʼ��������Ϊ��ֵ��ʼ������
				ʱ�临�Ӷȣ�O(max{ListSize, theList.listSize})
						




**/

// ���캯��
template <typename T>
chain<T> ::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;  // ����ַ�����
		s << "Initial capacity = " << initialCapacity << "Must be > 0";
		throw s.str();//illegalParameterValue(s.str());
	}
	firstNode = NULL;
	listSize = 0;

}

// ���ƹ��캯��
template <typename T>
chain <T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;
	if (listSize == 0)
	{
		// ����theListΪ��
		firstNode = NULL;
			return;
	}

	// ����theListΪ�ǿ�
	chainNode<T>* sourceNode = theList.firstNode;  // Ҫ��������theList�Ľڵ㣬����sourceNode��������ָ���һ���ڵ��ָ�룬��������ڵ��������theList��firstNode�Ŀ���
	firstNode = new chainNode<T>(sourceNode->element);  // ��������theList����Ԫ�أ���ĳ�Ա���ݣ�ָ��ǰ����ĵ�һ���ڵ��ָ��
	sourceNode = sourceNode->next;  // ��ʱsourceNodeָ����theList�ĵڶ����ڵ�
	chainNode<T>* targetNode = firstNode;  // targetNode��ʾ��ǰ����*this�����һ���ڵ㣬��ʱ��ָ���һ���ڵ��
	while (sourceNode != NULL)  // ����ʣ��Ԫ��
	{
		targetNode->next = new chainNode<T>(sourceNode->element);  // ��һ��ִ���ǿ���theList�ĵڶ����ڵ㣬����������ƶ�
		targetNode = targetNode->next;  // ��ǰ�����ƶ�����һ���ڵ�
		sourceNode = sourceNode->next;  // theList�������һ���ڵ�
	}
	targetNode->next = NULL;  // �������
}

/***************��������************************
* ��������~chain()
* �������ܣ���������������ɾ����������нڵ�
* ����ʹ�ã������ٶ���ʱ�Զ�ִ�У�һ����ֻ����һ������������

**/

template<typename T>
chain<T> ::~chain()
{
	while (firstNode != NULL)  // ɾ���׽ڵ�
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

/**************   get����      *****************
* ��������
* ����������int���͵�����theIndex
* ��������ֵ��������theIndex��Ԫ��,����Ԫ�ز����ڣ��׳��쳣
* ����ʵ�֣��ӵ�һ���ڵ㿪ʼ����������nextֱ���ҵ�����ڵ��λ��
* ʱ�临�Ӷȣ�O(theIndex)


*/

template<typename T>
T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);  // ����Ԫ���Ƿ����

	// ��������Ҫ�Ľڵ�
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; ++i)
		currentNode = currentNode->next;
	return currentNode->element;
}


/**************����˵��***************
* ��������indexOf(const T& theElement)const
* ����������һ����������Ԫ��������ͬ��Ԫ��ֵ
* ��������ֵ: ����Ԫ��theElement�״γ��ֵ�����,�������ڣ�����-1
* ʱ�临�Ӷȣ�O(listSize)



**/

template<typename T>
int chain<T>::indexOf(const T& theElement)const
{
	// ��������Ѱ��Ԫ��theElement
	chainNode<T>* currentNode = firstNode;
	int index = 0; // ��ǰ�ڵ������
	while (currentNode != NULL && currentNode->element != theElement)
	{ 
		// ������һ���ڵ�
		currentNode = currentNode->next;
		index += 1;
	}
	// ȷ���Ƿ��ҵ�����Ԫ��
	if (currentNode == NULL)  // �˳�ѭ������ǵ���ĩβ��û���ҵ���˵����Ԫ�ز��������У�����-1
		return -1;
	else
		return index;


}

/***************����˵��**********************
* ��������erase(int theIndex)
* ����������int���ͣ�Ҫɾ���ڵ������
* ��������ֵ����
* �������ܣ�ɾ������ΪtheIndex��Ԫ��
* ���˵������Ҫ��������ϸ�ڣ�
				1��������Ч��
				2��ɾ���ǿ�����ĵ�0��Ԫ�ؽڵ㣬����Ԫ�ؽڵ㣻
				3��ɾ������Ԫ�ؽڵ�;
				4��ɾ���ڵ�֮������Ĵ�СҪ��Ӧ�����仯
* ʱ�临�Ӷȣ�O(theIndex)

**/
template <typename T>
void chain<T>::erase(int theIndex)
{
	// ��������Ƿ���Ч,����Ч���׳��쳣
	checkIndex(theIndex);  

	// ��������Ч��ɾ���ýڵ�
	chainNode<T>* deleteNode;
	if (theIndex == 0)  // ɾ��ͷ���
	{
		deleteNode =  firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* p = firstNode;  // ��ָ��pָ��Ҫɾ���ڵ��ǰ���ڵ�
		
		for (int index = 1; index != theIndex; ++index)  // ���˳�ѭ����pָ��Ҫɾ���ڵ��ǰ���ڵ�
		{
			p = p->next;  
			
		}
		deleteNode = p->next;  
		p->next = deleteNode->next;  // ɾ��deleteNodeָ��Ľڵ㣬����ɾ���ڵ��ǰ���ڵ�ָ����ָ��ָ��ɾ���ڵ��̽ڵ�
	}
	listSize -= 1;
	delete deleteNode;

}
/*****************����˵��***********************
* ��������insert(int theIndex, const T& theElement)
* ��������������ڵ��δ���������ڵ����ֵ
* ��������ֵ��
* ʱ�临�Ӷȣ�O(theIndex)



**/
template <typename T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	if (theIndex == 0)  // �ڱ�ͷ����
	{
		firstNode = new chainNode<T>(theElement, firstNode);  // new���ص��ǵ�ַ
	}
	else
	{
		chainNode<T>* p = firstNode;  // ����һ���ڵ�ָ��p����ʾ����λ�õ�ǰ���ڵ�
		// Ѱ��λ��
		for (int index = 1; index < theIndex; ++index)  // index=1��ʱ��ָ���0���ڵ㣬index=2��ʱ��ָ���1���ڵ�
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);  // �½��������Ľڵ�		

	}
	listSize += 1;
}
/****************����˵��***********************
* ��������checkIndex(int theIndex)const
* ����������int ��������
* ��������ֵ���գ���������Ч���׳��쳣




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




/******************����˵��******************
* ��������output(ostream& out)const
* �������������������
* ��������ֵ����
* ʵ�ֹ��ܣ�����������������
* ʱ�临�Ӷȣ�O(listSize)



**/

template <typename T>
void chain<T>::output(ostream& out)const
{
	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		
		out << currentNode->element << "  ";
	}
}
/******************����˵��**********************
* ��������operator<<(ostream& out, const chain<T>& x)
* �����������������������
* ��������ֵ�����������
* ����˵�������� <<
		���ص�������Ǵ����������Ƶĺ��������������ɹؼ���operator�����Ҫ���ص���������Ź��ɣ���һ���������ͺ�һ�������б�
**/
template <typename T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}

/********************����˵��*********************
* ��������clear()
* ������������
* ��������ֵ����
* �������ܣ��������ɾ����������нڵ�


**/

template <typename T>
void chain<T> ::clear()
{
	
	while (firstNode->next != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;  // һ��Ҫָ��Ҫɾ���ڵ����һ���ڵ㣬����ɾ������ڵ�֮������ڵ��ָ�����û�������ˣ��Ҳ�����һ���ڵ�
		delete firstNode;
		firstNode = nextNode;
	}
	listSize = 0;
}
/***************����˵��**********************
* ��������
* ����������
* ��������ֵ��
* ����˵����ÿ�����Ӷ��Եײ��ڵ���Ϊ�׽ڵ㣬�����ڵ���Ϊβ��㡣ÿ�����Ӷ�������ָ�룬�ֱ�洢������bottom��top�У�
			�ֱ�ָ��β�����нڵ㡣bottom[theBin]ָ������theBin��β��㣬��top[theBin]ָ������theBin���׽ڵ㡣�������ӿ�ʼΪ�ձ�
			��ʱbottom[theBin]=NULL

**/
template <typename T>
void chain<T>::binSort(int range)
{
	// �������еĽڵ�����
	// ��������ʼ������
	chainNode<T>** bottom, ** top;  // ������β�ڵ�
	int len = range + 1;
	bottom = new chainNode<T>* [len];  // ָ��ڵ�ָ���ָ��
	top = new chainNode<T>* [len];  // ָ��ڵ�ָ���ָ��
	for (int b = 0; b <= range; ++b)
	{
		bottom[b] = NULL;
	}
	// ������Ľڵ���������
	for (; firstNode != NULL;firstNode = firstNode->next)
	{
		// ���׽ڵ�ӵ�������
		int theBin = firstNode->element;  // Ԫ������ת��������,�������
		if (bottom[theBin] == NULL)  // ����Ϊ��
			bottom[theBin] = top[theBin] = firstNode;
		else  // ���Ӳ�Ϊ��
		{
			top[theBin]->next = firstNode;
			top[theBin] = firstNode;  // ????
		}
	}

	// �������еĽڵ��ռ�����������
	chainNode<T>* y = NULL;
	for (int theBin = 0; theBin <= range; ++theBin)
	{
		if (bottom[theBin] != NULL) // ���Ӳ�Ϊ��
		{
			if (y == NULL)  // ��һ�����ӷǿ�
				firstNode = bottom[theBin];
			else
				y->next = bottom[theBin];  // ���ǵ�һ���ǿ�����
			y = top[theBin];
		}


	}
	if (y != NULL)
		y->next = NULL;
	   	  
	delete[] top;
	delete[] bottom;

}




#endif


