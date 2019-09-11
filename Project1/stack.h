
#ifndef __STACK_H__
#define __STACK_H__

#include "common.h"

#define INIT_SIZE 20
#define INCREMENT_SIZE 5
typedef int SElemType;


/*
存储结构
*/
typedef struct
{
	SElemType* base;  // 栈尾指针
	SElemType* top;  // 栈顶指针
	int size;  // 栈的大小
}SqStack;

int TestStack();

#endif 

