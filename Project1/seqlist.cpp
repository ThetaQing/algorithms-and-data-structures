# include <iostream>
# include "seqlist.h"
using namespace std;



/*
初始化一个空的线性表
*/
Status InitSeqList(Sqlist* L)
{
	L->elem = (Elemtype*)malloc(INIT_SIZE * sizeof(Elemtype));  // 分配存储空间
	if (!L->elem)
	{
		return ERROR;
	}  // 如果分配内存失败，操作失败，否则对结构体的成员变量初始化
	L->length = 0;
	L->size = INIT_SIZE;
	return OK;
}

/*
销毁线性表
*/
Status DestroySeqList(Sqlist* L)
{
	free(L->elem);  // 释放指针所指的存储空间
	L->length = 0;  // 结构体内元素置零
	L->size = 0;
	return OK;
}
/*
清空线性表
*/
Status ClearSeqList(Sqlist *L)
{
	L->length = 0;  // ？？？？？？？
	return OK; 
}
/*
判断线性表是否为空
*/
Status isSeqEmpty(Sqlist L)
{
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}
/*
获取长度
*/
int getLength(const Sqlist L)
{
	return L.length;
}

/*
插入元素
*/
Status InsertElem(Sqlist* L, int i, Elemtype e)
{
	Elemtype *newelem;
	if (i < 1 || i > L->length + 1)
	{
		cout << "Wrong position" << endl;
		return ERROR;
	}
	// 如果内存空间不足，需要添加内存
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
	// 从第i个元素开始全部向后移动一个位置
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
删除元素并返回它的值
*/
Status DeletSeqElem(Sqlist* L, int i, Elemtype* e)
{
	if (i < 1 || i >= L->length)
	{
		return ERROR;
	}
	Elemtype* p = &L->elem[i-1];  // 第i个位置的数组索引是[i - 1]
	*e = *p;  // 返回值？？？
	for (; p < &L->elem[L->length]; p++)
	{
		*(p) = *(p+1);
	}
	--L->length;
	return OK;
}

/*
根据位置获取元素
*/
Status GetSeqElem(const Sqlist L, int i, Elemtype* e)
{
	if (i<1 || i> L.length)
	{
		return ERROR;
	}
	*e = L.elem[i - 1];  // 直接采用下标索引,第i个元素数组索引是[i - 1]
	return OK;
}
/*
比较两个元素是否相等
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
顺序查找
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
	// 顺序比较每一个列表的元素
	// 如果没有找到对应元素，操作失败
	if (i >= L.length)
	{
		return ERROR;
	}
}

/*
*查找前驱元素
*/
Status PreSeqElem(const Sqlist L, Elemtype cur_e, Elemtype* pre_e)
{
	int i;
	// 顺序比较每一个列表中的元素，如果找到了并且不是头结点元素，返回前驱节点，否则操作失败
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
*查找后继节点
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
访问元素
*/
void visitSeqElem(Elemtype e)
{
	cout << dec << e << endl;
}

/*
遍历线性表
*/
Status TraverseSeqList(const Sqlist L, void (*visit)(Elemtype))
{
	for (int i = 0; i < L.length; ++i)
	{
		visit(L.elem[i]);  // 什么时候可以访问0，什么时候没有？
	}
	return OK;
}
/*
测试函数
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
