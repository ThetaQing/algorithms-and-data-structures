
#include "binarytree.h"

using namespace std;


/*����������������0��ʾ��������*/
Status CreateBiTree(BiTree* T)
{
	TElemType e;
	cout << "�Ƿ񴴽���������������0����������ڵ�ֵ�� ";
	cin >> e;
	
	if (e == 0)
		* T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(OVERFLOW);
		
		(*T)->data = e;  // T��ʾ���ǵ�ַ��*T��ʾ��Tָ��Ľڵ㣬(*T)->data��ʾ�ڵ��data
		cout << "�������ڵ�" << endl;
		
		CreateBiTree(&(*T)->lchild);
		cout << "������ڵ�" << endl;
		
		CreateBiTree(&(*T)->rchild);  // ???�����ַ
		cout << "�����ҽڵ�" << endl;
	}
	return OK;

}

/*����Ԫ��*/
void VisitBiTree(TElemType e)
{
	cout << e << endl;
}

/*�������*/
void PreOrderTraverse(BiTree T, void (*visit) (TElemType))
{
	if (T)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
	}
}

/*�������*/
void InOrderTraverse(BiTree T, void (*visit)(TElemType))
{
	if (T)
	{
		InOrderTraverse(T->lchild, visit);
		visit(T->data);
		InOrderTraverse(T->rchild, visit);
	}
}

/*�������*/
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
	cout << "��ʼ����" << endl;
	CreateBiTree(&T);
	cout << "�������" << endl;
	PreOrderTraverse(T, *VisitBiTree);
	cout << "�������" << endl;
	InOrderTraverse(T, *VisitBiTree);
	cout << "�������" << endl;
	PostOrderTraverse(T, *VisitBiTree);
}