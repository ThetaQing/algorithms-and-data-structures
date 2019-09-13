
#include "binarytree.h"

using namespace std;


/*创建二叉树，输入0表示创建空树*/
Status CreateBiTree(BiTree* T)
{
	TElemType e;
	cout << "是否创建空树，是请输入0，否则输入节点值： ";
	cin >> e;
	
	if (e == 0)
		* T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(OVERFLOW);
		
		(*T)->data = e;  // T表示的是地址，*T表示的T指向的节点，(*T)->data表示节点的data
		cout << "创建根节点" << endl;
		
		CreateBiTree(&(*T)->lchild);
		cout << "创建左节点" << endl;
		
		CreateBiTree(&(*T)->rchild);  // ???传入地址
		cout << "创建右节点" << endl;
	}
	return OK;

}

/*访问元素*/
void VisitBiTree(TElemType e)
{
	cout << e << endl;
}

/*先序遍历*/
void PreOrderTraverse(BiTree T, void (*visit) (TElemType))
{
	if (T)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
	}
}

/*中序遍历*/
void InOrderTraverse(BiTree T, void (*visit)(TElemType))
{
	if (T)
	{
		InOrderTraverse(T->lchild, visit);
		visit(T->data);
		InOrderTraverse(T->rchild, visit);
	}
}

/*后序遍历*/
void PostOrderTraverse(BiTree T, void(*visit)(TElemType))
{
	if (T)
	{
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T->data);
	}
}
/*test*/
void TestBiTree()
{
	BiTree T;
	cout << "开始创建" << endl;
	CreateBiTree(&T);
	cout << "先序遍历" << endl;
	PreOrderTraverse(T, *VisitBiTree);
	cout << "中序遍历" << endl;
	InOrderTraverse(T, *VisitBiTree);
	cout << "后序遍历" << endl;
	PostOrderTraverse(T, *VisitBiTree);
}