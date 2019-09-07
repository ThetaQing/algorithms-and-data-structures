# include <iostream>
# include "seqlist.h"
using namespace std;



/*
��ʼ��һ���յ����Ա�
*/
Status InitSeqList(Sqlist* L)
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
Status DestroySeqList(Sqlist* L)
{
	free(L->elem);  // �ͷ�ָ����ָ�Ĵ洢�ռ�
	L->length = 0;  // �ṹ����Ԫ������
	L->size = 0;
	return OK;
}
/*
������Ա�
*/
Status ClearSeqList(Sqlist *L)
{
	L->length = 0;  // ��������������
	return OK; 
}
/*
�ж����Ա��Ƿ�Ϊ��
*/
Status isSeqEmpty(Sqlist L)
{
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}
/*
��ȡ����
*/
int getLength(const Sqlist L)
{
	return L.length;
}

/*
����Ԫ��
*/
Status InsertElem(Sqlist* L, int i, Elemtype e)
{
	Elemtype *newelem;
	if (i < 1 || i > L->length + 1)
	{
		cout << "Wrong position" << endl;
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
	Elemtype *p = &L->elem[i - 1];
	Elemtype *q = &L->elem[L->length - 1];



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
Status DeletSeqElem(Sqlist* L, int i, Elemtype* e)
{
	if (i < 1 || i >= L->length)
	{
		return ERROR;
	}
	Elemtype* p = &L->elem[i-1];  // ��i��λ�õ�����������[i - 1]
	*e = *p;  // ����ֵ������
	for (; p < &L->elem[L->length]; p++)
	{
		*(p) = *(p+1);
	}
	--L->length;
	return OK;
}

/*
����λ�û�ȡԪ��
*/
Status GetSeqElem(const Sqlist L, int i, Elemtype* e)
{
	if (i<1 || i> L.length)
	{
		return ERROR;
	}
	*e = L.elem[i - 1];  // ֱ�Ӳ����±�����,��i��Ԫ������������[i - 1]
	return OK;
}
/*
�Ƚ�����Ԫ���Ƿ����
*/
Status compareSeq(Elemtype e1, Elemtype e2)
{
	if (e1 == e2)
		return 0;
	else if (e1 < e2)
		return -1;
	else
		return 1;
}


/*
˳�����
*/
Status FindSeqElem(const Sqlist L, Elemtype e, Status(*compareSeq)(Elemtype, Elemtype))
{
	int i;
	for (i = 0; i < L.length; ++i)
	{
		if (!(*compareSeq)(L.elem[i], e))
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
Status PreSeqElem(const Sqlist L, Elemtype cur_e, Elemtype* pre_e)
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
Status NextSeqElem(const Sqlist L, Elemtype cur_e, Elemtype* next_e)
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
/*
����Ԫ��
*/
void visitSeqElem(Elemtype e)
{
	cout << dec << e << endl;
}

/*
�������Ա�
*/
Status TraverseSeqList(const Sqlist L, void (*visit)(Elemtype))
{
	for (int i = 0; i < L.length; ++i)
	{
		visit(L.elem[i]);  // ʲôʱ����Է���0��ʲôʱ��û�У�
	}
	return OK;
}
/*
���Ժ���
*/
int testSeqList()
{
	Sqlist L;
	if (InitSeqList(&L))
	{
		Elemtype e;
		cout << "init_success" << endl;
		if (isSeqEmpty(L))
			cout << "the list is empty" << endl;
		else
			cout << "the list is not empty" << endl;
		for (int i = 0; i < 10; ++i)
			InsertElem(&L, i + 1, i);

		cout << "length of list: " << getLength(L) << endl;
		if (GetSeqElem(L, 1, &e))
			cout << "the first element is : " << dec << e << endl;
		
		cout << "the element 5 at : " << FindSeqElem(L, 5, *compareSeq) << endl;

		cout << "visit the first element: ";
		visitSeqElem(L.elem[0]);

		PreSeqElem(L, 6, &e);
		cout << "the 6's previous element is : " << e << endl;
		NextSeqElem(L, 6, &e);
		cout << "the 6's next element is : " << e << endl;

		cout << "List:" << endl;
		TraverseSeqList(L, visitSeqElem);
		DeletSeqElem(&L, 1, &e);
		cout << "delete the first element :" << e << endl;



		if (DestroySeqList(&L))
			cout << "destroy success" << endl;

		return 0;

	}
}
