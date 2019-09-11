#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include <iostream>
#include "common.h"
using namespace std;
typedef int Elemtype;  // 定义结构体元素的类型
typedef int Status;  // 定义别名
/*
存储结构
*/
typedef struct LNode
{
	Elemtype data;
	struct LNode* next;
}LNode, * LinkList;

void ClearLinkList(LinkList L);
Status compaCompareLinkListElemre(Elemtype e1, Elemtype e2);
Status DeleteLinkListElem(LinkList L, int i, Elemtype* e);
void DestroyLinkList(LinkList* L);
int FindLinkListElem(LinkList L, Elemtype e, Status(*compare)(Elemtype, Elemtype));
Status GetLinkListElem(LinkList L, int i, Elemtype* e);
int GetLinkListLength(LinkList L);
void InitLinkList(LinkList* L);
Status InsertLinkListElem(LinkList L, int i, Elemtype e);
Status isLinkListEmpty(LinkList L);
Status NextLinkListElem(LinkList L, Elemtype e, Elemtype* next_e);
Status PreLinkListElem(LinkList L, Elemtype cur_e, Elemtype* pre_e);
int testLinkList();
void TraverseLinkList(LinkList L, void(*visit)(Elemtype));
void visitLinkList(Elemtype e);

#endif 

