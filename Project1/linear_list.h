#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__
// ���Ա�ĳ�����
template<typename T>
class linearList
{
public:
	virtual ~linearList() {};  // ��������
	virtual bool empty() const = 0; // ���ҽ������Ա�Ϊ��ʱ����true��const��ʾ��������ڲ����޸���ĳ�Ա�����������Ǹ���Ա����ʱmutable��
	virtual int size()const = 0;  // �������Ա��Ԫ�ظ���
	virtual T& get(int theIndex) const = 0;  // ��������ΪtheIndex��Ԫ��
	virtual void erase(int theIndex) = 0;  // ɾ������ΪtheIndex��Ԫ��
	virtual void insert(int theIndex, const T& theElement) = 0;  // ��theElement�������Ա�������ΪtheIndex��λ����
	virtual void output(ostream& out) const = 0;  // �����Ա���������out
};

// ����ڵ�Ľṹ����
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
	chainNode(const T& element, chainNode<T>* next)
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
	

	 // ɾ������ΪtheIndex��Ԫ��
	void erase(int theIndex);


	 // ��theElement�������Ա�������ΪtheIndex��λ����
	void insert(int theIndex, const T& theElement);


	 // �����Ա���������out
	void output(ostream& out) const;



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
		throw illegalParameterValue(s.str());
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
	for (int i = 0l i < theIndex; ++i)
		currentNode = currentNode->next;
	return currentNode->element;
}





#endif


