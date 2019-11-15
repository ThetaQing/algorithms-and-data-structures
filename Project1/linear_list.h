#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__
// ���Ա�ĳ�����
template<typename T>
class linearList
{
public:
	virtual ~linearList() {};  // ��������
	virtual bool empty() const = 0; // ���ҽ������Ա�Ϊ��ʱ����true
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

template<typename T>
class chain : public linearList<T>
{
public:
	// ���캯�������ƹ��캯������������
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	// ������������ADT�ķ���

};

#endif // !__LINEAR_LIST_H__

