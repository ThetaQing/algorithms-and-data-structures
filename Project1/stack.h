
#ifndef __STACK_H__
#define __STACK_H__

#include "common.h"

#define INIT_SIZE 20
#define INCREMENT_SIZE 5
typedef int SElemType;


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

