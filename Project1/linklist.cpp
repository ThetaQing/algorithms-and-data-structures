#include <iostream>
# include"linklist.h"

using namespace std;

/******************************
*      链式表     *
*
*/


/*
*初始化链式表
*/
void InitLinkList(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	(*L)->next = NULL;
}

/*
*销毁链表，不存在该链表了
*/
void DestroyLinkList(LinkList* L)  // (LinkList* L)表示这个指针指向的内存空间
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
Status InsertLinkListElem(LinkList L, int i, Elemtype e)
{
	int j = 0; 
	LinkList s, p = L;
	// 先找到插入位置的前一个位置处的结点
	while (p && j < i - 1)
	{
		++j;
		p = p->next;
	} 
	
	if (!p || j > i - 1)
		return ERROR;
	// 分配内存
	s = (LinkList)malloc(sizeof(LNode));  // 链表存储是不相邻的
	// 添加第i个结点s
	// 插入结点
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
/*
*删除元素
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
		return ERROR;  // 如果删除的是尾结点报错
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
清空线性表,变成了空表
*/
void ClearLinkList(LinkList L)
{
	LinkList p = L->next;
	L->next = NULL;
	DestroyLinkList(&p);
}

/*
判断是否为零
*/
Status isLinkListEmpty(LinkList L)
{
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

/*
获取长度
*/
int GetLinkListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;  // 如果是空表，返回0
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
查找指定元素的位置
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
获取前驱元素
*/
Status PreLinkListElem(LinkList L, Elemtype cur_e, Elemtype *pre_e)
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
访问元素
*/
void visitLinkList(Elemtype e)
{
	cout << dec <<e << endl;  // 输出十进制数

}
/*
遍历线性表
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