# include <iostream>
using namespace std;

# define INIT_SIZE 10  // ��ʼ���б�
# define INCREMENT_SIZE 5  // ��������
# define OK 1  // �����ɹ�
# define ERROR 0  // ����ʧ��

typedef int Elemtype;  // ����ṹ��Ԫ�ص�����
typedef int Status;  // �������

/*
����һ���ṹ��
*/
typedef struct
{
	Elemtype *elem;  // �洢�ռ��ַ
	int length;  // ��ǰ����
	int size;  // ��ǰ����ı���С

}Sqlist;

/*
��ʼ��һ���յ����Ա�
*/
Status InitList(Sqlist* L)
{
	L->elem = (Elemtype*)malloc(INIT_SIZE * sizeof(Elemtype));  // ����洢�ռ�
	if (!L->elem)
	{
		return ERROR;
	}  // ��������ڴ�ʧ�ܣ�����ʧ�ܣ�����Խṹ��ĳ�Ա������ʼ��
	L->length = 0;
	L->size = INIT_SIZE;
	return OK;
}

/*
�������Ա�
*/
Status DestroyList(Sqlist* L)
{
	free(L->elem);  // �ͷ�ָ����ָ�Ĵ洢�ռ�
	L->length = 0;  // �ṹ����Ԫ������
	L->size = 0;
	return OK;
}
/*
����Ԫ��
*/
Status InsertElem(Sqlist* L, int i, Elemtype e)
{
	Elemtype *newelem;
	if (i < 1 || L->length + 1)
	{
		return ERROR;
	}
	// ����ڴ�ռ䲻�㣬��Ҫ����ڴ�
	if (L->length >= L->size)
	{
		newelem = (Elemtype*)realloc(L->elem, (L->size + INCREMENT_SIZE) * sizeof(Elemtype));
		if (!newelem)
		{
			return ERROR;
		}
		L->elem = newelem;
		L->size += INCREMENT_SIZE;
	}
	// �ӵ�i��Ԫ�ؿ�ʼȫ������ƶ�һ��λ��
	Elemtype *p = &(L->elem[i - 1]);
	Elemtype *q = &(L->elem[L->length - 1]);



	for (; q >= p; q--)
	{
		*(q + 1) = *q;
	}
	*p = e;
	++L->length;
	return OK;
}
/*
ɾ��Ԫ�ز���������ֵ
*/
Status DeletElem(Sqlist* L, int i, Elemtype* e)
{
	if (i < 1 || i >= L->length)
	{
		return ERROR;
	}
	Elemtype* p = &L->elem[i];
	*e = *p;  // ����ֵ������
	Elemtype* q = &L->elem[L->length - 1];
	for (; q >= p; p++)
	{
		*(p - 1) = *p;
	}
	--L->length;
	return OK;
}

/*
����λ�û�ȡԪ��
*/
Status GetElem(const Sqlist L, int i, Elemtype* e)
{
	if (i<1 || i> L.length)
	{
		return ERROR;
	}
	*e = L.elem[i - 1];  // ֱ�Ӳ����±�����
	return OK;
}

/*
˳�����
*/
Status FindElem(const Sqlist L, Elemtype e, Status(*compare)(Elemtype, Elemtype))
{
	int i;
	for (i = 0; i < L.length; ++i)
	{
		if (!(*compare)(L.elem[i], e))
		{
			return i + 1;
		}
	}
	// ˳��Ƚ�ÿһ���б��Ԫ��
	// ���û���ҵ���ӦԪ�أ�����ʧ��
	if (i >= L.length)
	{
		return ERROR;
	}
}

/*
*����ǰ��Ԫ��
*/
Status PreElem(const Sqlist L, Elemtype cur_e, Elemtype* pre_e)
{
	int i;
	// ˳��Ƚ�ÿһ���б��е�Ԫ�أ�����ҵ��˲��Ҳ���ͷ���Ԫ�أ�����ǰ���ڵ㣬�������ʧ��
	for (i = 0; i < L.length; ++i)
	{
		if (cur_e == L.elem[i])
		{
			if (i)
			{
				*pre_e = L.elem[i - 1];
				return OK;
			}
			else
				return ERROR;
		}
	}
	return ERROR;
}
/*
*���Һ�̽ڵ�
*/
Status NextElem(const Sqlist L, Elemtype cur_e, Elemtype* next_e)
{
	for (int i = 0; i < L.length; ++i)
	{
		if (cur_e == L.elem[i])
		{
			if (L.length - i != 1)
			{
				*next_e = L.elem[i + 1];
				return OK;
			}
			else
				return ERROR;
		}
	}
	return ERROR;
}


