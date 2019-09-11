# include <iostream>
# include "stack.h"
using namespace std;



/*初始化栈*/
Status InitStack(SqStack* S)
{
	S->base = (SElemType*)malloc(INIT_SIZE * sizeof(SElemType));
	if (!S->base)
		exit(OVERFLOW);
	S->top = S->base;
	S->size = INIT_SIZE;
	return OK;
}

/*销毁栈*/
Status DestroyStack(SqStack* S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->size = 0;
	return OK;
}

/*清空栈*/
Status ClearStack(SqStack* S)
{
	S->base = S->top;  // 那些元素去哪儿了？
	return OK;
}

/*判断是否为空*/
Status IsEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;

}
/*获取栈的长度*/
int GetLength(SqStack S)
{
	return S.top - S.base;
}

/*获取栈顶元素*/
Status GetTop(SqStack S, SElemType  &e)
{
	if (S.top > S.base)
	{
		e = *(--S.top);  // top表示栈顶，指向栈顶的下一个位置
		return OK;
	}
	else
		return ERROR;
}

/*压栈*/
Status Push(SqStack* S, SElemType e)
{
	if ((S->top - S->base) / sizeof(SElemType) >= S->size)
	{
		S->base = (SElemType*)realloc(S->base, (S->size + INCREMENT_SIZE) * sizeof(SElemType));
		if (!S->base)
			exit(OVERFLOW);
		S->top = S->base + S->size;
		S->size += INCREMENT_SIZE;
	}
	*S->top = e;
	S->top++;
	return OK;
}

/*退栈*/
Status Pop(SqStack* S, SElemType &e)  // 使用传引用参数，P188.
{
	if (S->base == S->top)
		return ERROR;
	else
	{
		--(S->top);
		e = *S->top;
		return OK;
	}		
}

/*访问元素*/
void visit(SElemType e)
{
	cout << e << endl;
}

/*遍历栈*/
Status TraverseStack(SqStack S, void(*visit)(SElemType))
{
	while (S.top >= S.base)
	{
		
		visit(*S.base);
		S.base++;
	}
	return OK;
}

/*测试栈代码*/
int TestStack()
{
	SqStack S;
	if (InitStack(&S))
	{
		SElemType e;
		cout << "init succuss" << endl;
		if (IsEmpty(S))
			cout << "Stack is empty" << endl;
		for (int i = 0; i < 10; ++i)
			Push(&S, i);
		GetTop(S, e);
		cout << "the top element is : " << e << endl;
		cout << "the length of stack is : " << GetLength(S) << endl;
		Pop(&S, e);
		cout << "pop element is : " << e << endl;
		TraverseStack(S, *visit);
		if (DestroyStack(&S))
			cout << "destroy success." << endl;
			   
	}
	return 0;
}