#pragma once
#ifndef __SEQLIST_H__
#define __SEQLIST_H__

# define INIT_SIZE 10  // ��ʼ���б�
# define INCREMENT_SIZE 5  // ��������
# define OK 1  // �����ɹ�
# define ERROR 0  // ����ʧ��
# define TRUE 1  // ��
# define FALSE 0  // ��

typedef int Elemtype;  // ����ṹ��Ԫ�ص�����
typedef int Status;  // �������

/*
����һ���ṹ��
*/
typedef struct
{
	Elemtype* elem;  // �洢�ռ��ַ
	int length;  // ��ǰ����
	int size;  // ��ǰ����ı���С

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
