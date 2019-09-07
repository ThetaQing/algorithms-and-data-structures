#include <iostream>
# include"linklist.h"

using namespace std;

/******************************
*      ��ʽ��     *
*
*/


/*
*��ʼ����ʽ��
*/
void InitLinkList(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	(*L)->next = NULL;
}

/*
*�������������ڸ�������
*/
void DestroyLinkList(LinkList* L)  // (LinkList* L)��ʾ���ָ��ָ����ڴ�ռ�
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
Status InsertLinkListElem(LinkList L, int i, Elemtype e)
{
	int j = 0; 
	LinkList s, p = L;
	// ���ҵ�����λ�õ�ǰһ��λ�ô��Ľ��
	while (p && j < i - 1)
	{
		++j;
		p = p->next;
	} 
	
	if (!p || j > i - 1)
		return ERROR;
	// �����ڴ�
	s = (LinkList)malloc(sizeof(LNode));  // ����洢�ǲ����ڵ�
	// ��ӵ�i�����s
	// ������
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
/*
*ɾ��Ԫ��
*/
Status DeleteLinkListElem(LinkList L, int i, Elemtype* e)
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
		return ERROR;  // ���ɾ������β��㱨��
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
Status GetLinkListElem(LinkList L, int i, Elemtype* e)
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
������Ա�,����˿ձ�
*/
void ClearLinkList(LinkList L)
{
	LinkList p = L->next;
	L->next = NULL;
	DestroyLinkList(&p);
}

/*
�ж��Ƿ�Ϊ��
*/
Status isLinkListEmpty(LinkList L)
{
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

/*
��ȡ����
*/
int GetLinkListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;  // ����ǿձ�����0
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
Status compaCompareLinkListElemre(Elemtype e1, Elemtype e2)
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
int FindLinkListElem(LinkList L, Elemtype e, Status(*compare)(Elemtype, Elemtype))
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
Status PreLinkListElem(LinkList L, Elemtype cur_e, Elemtype *pre_e)
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
Status NextLinkListElem(LinkList L, Elemtype e, Elemtype* next_e)
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
void visitLinkList(Elemtype e)
{
	cout << dec <<e << endl;  // ���ʮ������

}
/*
�������Ա�
*/
void TraverseLinkList(LinkList L, void(*visit)(Elemtype))
{
	LinkList p = L->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
}


int testLinkList()
{
	LinkList L;
	InitLinkList(&L);
	Elemtype e;
	int i;
	if (L)
		cout << "Init success" << endl;
	if (isLinkListEmpty(L))
		cout << "list is emoty" << endl;
	for (i = 0; i < 100; i++)
		InsertLinkListElem(L, i + 1, i);
	if (GetLinkListElem(L, 1, &e))
		cout << "the first element is " << dec << e << endl;

	cout << "the length of L is " << dec << GetLinkListLength(L) << endl;
	cout << "the 5 at " << dec << FindLinkListElem(L, 5, *compaCompareLinkListElemre) << endl;

	PreLinkListElem(L, 6, &e);
	cout << "the 6's previous element is " << dec << e << endl;

	NextLinkListElem(L, 6, &e);
	cout << "the 6's next element is " << dec << e << endl;

	DeleteLinkListElem(L, 1, &e);
	cout << "delete first element : " << dec << e << endl;

	cout << "list is :" << endl;
	TraverseLinkList(L, visitLinkList);
	ClearLinkList(L);
	cout << "After clear, the length of L is " << dec << GetLinkListLength(L) << endl;
	DestroyLinkList(&L);
	if (!L)
		cout << "destroy success" << endl;

	return 0;
}