#pragma once
#include <iostream>
# define OK 1  // 操作成功
# define ERROR 0  // 操作失败
# define TRUE 1  // 操作成功
# define FALSE 0  // 操作失败
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

void ClearList(LinkList L);
Status compare(Elemtype e1, Elemtype e2);
Status DeleteElem(LinkList L, int i, Elemtype* e);
void DestroyList(LinkList* L);
int FindElem(LinkList L, Elemtype e, Status(*compare)(Elemtype, Elemtype));
Status GetElem(LinkList L, int i, Elemtype* e);
int GetLength(LinkList L);
void InitList(LinkList* L);
Status isEmpty(LinkList L);
Status NextElem(LinkList L, Elemtype e, Elemtype* next_e);
Status PreElem(LinkList L, Elemtype cur_e, Elemtype* pre_e);
int testChainedList();
void TraverseList(LinkList L, void(*visit)(Elemtype));
void visit(Elemtype e);
