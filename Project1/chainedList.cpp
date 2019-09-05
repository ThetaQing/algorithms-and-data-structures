#include <iostream>
# include"chainedlist.h"
# define OK 1  // �����ɹ�
# define ERROR 0  // ����ʧ��
# define TRUE 1  // �����ɹ�
# define FALSE 0  // ����ʧ��
using namespace std;

/******************************
*      ��ʽ��     *
*
*/


/*
*��ʼ����ʽ��
*/
void InitList(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	(*L)->next = NULL;
}

/*
*��������
*/
void DestroyList(LinkList* L)
{
	LinkList temp;
	while (*L)
	{
		temp = (*L)->next;
		free(*L);
		*L = temp;
	}
}
/*
����Ԫ��
*/
Status InsertElem(LinkList L, int i, Elemtype e)
{
	int j = 0; 
	LinkList s, p = L;
	// ���ҵ�����λ�ô��Ľ��
	while (p && j < i - 1)
	{
		j++;
		p = p->next;
	}
	if (!p || j > i - 1)
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	// ������
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
/*
*ɾ��Ԫ��
*/
Status DeleteElem(LinkList L, int i, Elemtype* e)
{
	int j = 0;
	LinkList p = L; 
	LinkList q = L;
	while (p->next && j < i - 1)
	{
		++j;
		p = p->next;
	}
	if (!p->next || j > i - 1)
		return ERROR;
	// ɾ��q���
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}
/*
����λ�û�ȡԪ��
*/
Status GetElem(LinkList L, int i, Elemtype* e)
{
	int j = 1;
	LinkList p = L->next;
	while (p && j < i)
	{
		j++;
		p = p->next;
	}
	if (!p || j > i)
		return ERROR;
	*e = p->data;
	return OK;
}
/*
������Ա�
*/
void ClearList(LinkList L)
{
	LinkList p = L->next;
	L->next = NULL;
	DestroyList(&p);
}

/*
�ж��Ƿ�Ϊ��
*/
Status isEmpty(LinkList L)
{
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

/*
��ȡ����
*/
int GetLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		++i;
		p = p->next;
	}
	return i;
}
 
/*
�Ƚ�����Ԫ���Ƿ����
*/
Status compare(Elemtype e1, Elemtype e2)
{
	if (e1 == e2)
		return 0;
	else if (e1 < e2)
		return -1;
	else
		return 1;
}

/*
����ָ��Ԫ�ص�λ��
*/
int FindElem(LinkList L, Elemtype e, Status(*compare)(Elemtype, Elemtype))
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		++i;
		if (!compare(p->data, e))
			return i;
		p = p->next;
	}
	return 0;
}
/*
��ȡǰ��Ԫ��
*/
Status PreElem(LinkList L, Elemtype cur_e, Elemtype *pre_e)
{
	LinkList q, p = L;
	while (p->next)
	{

		q = p->next;  // ��ʱ�洢ǰ���ڵ�
		if (cur_e == q->data)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;
	}
	
}

/*
��ȡ���Ԫ��
*/
Status NextElem(LinkList L, Elemtype e, Elemtype* next_e)
{
	LinkList p = L;
	while (p->next)
	{
		
		if (p->data == e)
		{
			*next_e = p->next->data;
			return OK;
		}
		p = p->next;		
	}
	return ERROR;
}
/*
����Ԫ��
*/
void visit(Elemtype e)
{
	cout << dec <<e << endl;  // ���ʮ������

}
/*
�������Ա�
*/
void TraverseList(LinkList L, void(*visit)(Elemtype))
{
	LinkList p = L->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
}


int testChainedList()
{
	LinkList L;
	InitList(&L);
	Elemtype e;
	int i;
	if (L)
		cout << "Init success" << endl;
	if (isEmpty(L))
		cout << "list is emoty" << endl;
	for (i = 0; i < 100; i++)
		InsertElem(L, i + 1, i);
	if (GetElem(L, 1, &e))
		cout << "the first element is " << dec << e << endl;

	cout << "the length of L is " << dec << GetLength(L) << endl;
	cout << "the 5 at " << dec << FindElem(L, 5, *compare) << endl;

	PreElem(L, 6, &e);
	cout << "the 6's previous element is " << dec << e << endl;

	NextElem(L, 6, &e);
	cout << "the 6's next element is " << dec << e << endl;

	DeleteElem(L, 1, &e);
	cout << "delete first element" << dec << e << endl;

	cout << "list is :" << endl;
	TraverseList(L, visit);

	DestroyList(&L);
	if (!L)
		cout << "destroy success" << endl;

	return 0;
}