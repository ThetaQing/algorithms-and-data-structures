#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include "common.h"
typedef int TElemType;
/*´æ´¢½á¹¹*/
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

Status CreateBiTree(BiTree* T);
void InOrderTraverse(BiTree T, void (*visit)(TElemType));
void PostOrderTraverse(BiTree T, void(*visit)(TElemType));
void PreOrderTraverse(BiTree T, void (*visit) (TElemType));
void TestBiTree();
void VisitBiTree(TElemType e);

#endif // !1
