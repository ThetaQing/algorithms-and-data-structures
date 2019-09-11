# include <iostream>
# include "stack.h"
using namespace std;



/*��ʼ��ջ*/
Status InitStack(SqStack* S)
{
	S->base = (SElemType*)malloc(INIT_SIZE * sizeof(SElemType));
	if (!S->base)
		exit(OVERFLOW);
	S->top = S->base;
	S->size = INIT_SIZE;
	return OK;
}

/*����ջ*/
Status DestroyStack(SqStack* S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->size = 0;
	return OK;
}

/*���ջ*/
Status ClearStack(SqStack* S)
{
	S->base = S->top;  // ��ЩԪ��ȥ�Ķ��ˣ�
	return OK;
}

/*�ж��Ƿ�Ϊ��*/
Status IsEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;

}
/*��ȡջ�ĳ���*/
int GetLength(SqStack S)
{
	return S.top - S.base;
}

/*��ȡջ��Ԫ��*/
Status GetTop(SqStack S, SElemType  &e)
{
	if (S.top > S.base)
	{
		e = *(--S.top);  // top��ʾջ����ָ��ջ������һ��λ��
		return OK;
	}
	else
		return ERROR;
}

/*ѹջ*/
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

/*��ջ*/
Status Pop(SqStack* S, SElemType &e)  // ʹ�ô����ò�����P188.
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

/*����Ԫ��*/
void visit(SElemType e)
{
	cout << e << endl;
}

/*����ջ*/
Status TraverseStack(SqStack S, void(*visit)(SElemType))
{
	while (S.top >= S.base)
	{
		
		visit(*S.base);
		S.base++;
	}
	return OK;
}

/*����ջ����*/
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