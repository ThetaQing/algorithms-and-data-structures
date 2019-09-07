
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

