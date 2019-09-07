#pragma once
#ifndef __SEQLIST_H__
#define __SEQLIST_H__

# define INIT_SIZE 10  // 初始化列表长
# define INCREMENT_SIZE 5  // 分配增量
# define OK 1  // 操作成功
# define ERROR 0  // 操作失败
# define TRUE 1  // 真
# define FALSE 0  // 假

typedef int Elemtype;  // 定义结构体元素的类型
typedef int Status;  // 定义别名

/*
定义一个结构体
*/
typedef struct
{
	Elemtype* elem;  // 存储空间基址
	int length;  // 当前长度
	int size;  // 当前分配的表长大小

}Sqlist;

Status ClearSeqList(Sqlist* L);
Status compareSeq(Elemtype e1, Elemtype e2);
Status DeletSeqElem(Sqlist* L, int i, Elemtype* e);
Status DestroySeqList(Sqlist* L);
Status FindSeqElem(const Sqlist L, Elemtype e, Status(*compare)(Elemtype, Elemtype));
Status GetSeqElem(const Sqlist L, int i, Elemtype* e);
int getLength(const Sqlist L);
Status InitSeqList(Sqlist* L);
Status InsertElem(Sqlist* L, int i, Elemtype e);
Status isSeqEmpty(Sqlist L);
Status NextSeqElem(const Sqlist L, Elemtype cur_e, Elemtype* next_e);
Status PreSeqElem(const Sqlist L, Elemtype cur_e, Elemtype* pre_e);
int testSeqList();
Status TraverseSeqList(const Sqlist L, void (*visit)(Elemtype));
void visitSeqElem(Elemtype e);




#endif // 
