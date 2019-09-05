# include <iostream>
using namespace std;

# define INIT_SIZE 10  // 初始化列表长
# define INCREMENT_SIZE 5  // 分配增量
# define OK 1  // 操作成功
# define ERROR 0  // 操作失败

typedef int Elemtype;  // 定义结构体元素的类型
typedef int Status;  // 定义别名

/*
定义一个结构体
*/
typedef struct
{
	Elemtype *elem;  // 存储空间基址
	int length;  // 当前长度
	int size;  // 当前分配的表长大小

}Sqlist;

/*
初始化一个空的线性表
*/
Status InitList(Sqlist* L)
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
Status DestroyList(Sqlist* L)
{
	free(L->elem);  // 释放指针所指的存储空间
	L->length = 0;  // 结构体内元素置零
	L->size = 0;
	return OK;
}
/*
插入元素
*/
Status InsertElem(Sqlist* L, int i, Elemtype e)
{
	Elemtype *newelem;
	if (i < 1 || L->length + 1)
	{
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
	Elemtype *p = &(L->elem[i - 1]);
	Elemtype *q = &(L->elem[L->length - 1]);



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
Status DeletElem(Sqlist* L, int i, Elemtype* e)
{
	if (i < 1 || i >= L->length)
	{
		return ERROR;
	}
	Elemtype* p = &L->elem[i];
	*e = *p;  // 返回值？？？
	Elemtype* q = &L->elem[L->length - 1];
	for (; q >= p; p++)
	{
		*(p - 1) = *p;
	}
	--L->length;
	return OK;
}

/*
根据位置获取元素
*/
Status GetElem(const Sqlist L, int i, Elemtype* e)
{
	if (i<1 || i> L.length)
	{
		return ERROR;
	}
	*e = L.elem[i - 1];  // 直接采用下标索引
	return OK;
}

/*
顺序查找
*/
Status FindElem(const Sqlist L, Elemtype e, Status(*compare)(Elemtype, Elemtype))
{
	int i;
	for (i = 0; i < L.length; ++i)
	{
		if (!(*compare)(L.elem[i], e))
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
Status PreElem(const Sqlist L, Elemtype cur_e, Elemtype* pre_e)
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
Status NextElem(const Sqlist L, Elemtype cur_e, Elemtype* next_e)
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


