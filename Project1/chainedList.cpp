#include <iostream>
# include"chainedlist.h"
# define OK 1  // 操作成功
# define ERROR 0  // 操作失败
# define TRUE 1  // 操作成功
# define FALSE 0  // 操作失败
using namespace std;

/******************************
*      链式表     *
*
*/


/*
*初始化链式表
*/
void InitList(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	(*L)->next = NULL;
}

/*
*销毁链表
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
插入元素
*/
Status InsertElem(LinkList L, int i, Elemtype e)
{
	int j = 0; 
	LinkList s, p = L;
	// 先找到插入位置处的结点
	while (p && j < i - 1)
	{
		j++;
		p = p->next;
	}
	if (!p || j > i - 1)
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	// 插入结点
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
/*
*删除元素
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
	// 删除q结点
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}
/*
根据位置获取元素
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
清空线性表
*/
void ClearList(LinkList L)
{
	LinkList p = L->next;
	L->next = NULL;
	DestroyList(&p);
}

/*
判断是否为零
*/
Status isEmpty(LinkList L)
{
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

/*
获取长度
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
比较两个元素是否相等
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
查找指定元素的位置
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
获取前驱元素
*/
Status PreElem(LinkList L, Elemtype cur_e, Elemtype *pre_e)
{
	LinkList q, p = L;
	while (p->next)
	{

		q = p->next;  // 暂时存储前驱节点
		if (cur_e == q->data)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;
	}
	
}

/*
获取后继元素
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
访问元素
*/
void visit(Elemtype e)
{
	cout << dec <<e << endl;  // 输出十进制数

}
/*
遍历线性表
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