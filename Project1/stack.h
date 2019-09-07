
#ifndef __STACK_H__
#define __STACK_H__

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INIT_SIZE 20
#define INCREMENT_SIZE 5

typedef int SElemType;
typedef int Status;

/*
�洢�ṹ
*/
typedef struct
{
	SElemType* base;  // ջβָ��
	SElemType* top;  // ջ��ָ��
	int size;  // ջ�Ĵ�С
}SqStack;

int TestStack();

#endif 

