#pragma once
#ifndef __SEQLIST_H__
#define __SEQLIST_H__
#include "common.h"

# define INIT_SIZE 10  // 初始化列表长
# define INCREMENT_SIZE 5  // 分配增量




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
