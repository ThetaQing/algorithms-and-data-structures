# include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int QElemType;
typedef int Status;

/*存储结构*/
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;  // 队头指针
	QueuePtr rear;  // 队尾指针
}LinkQueue;

/*初始化队列*/
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front = Q->rear = NULL;
	return OK;                                                                                             
}
/*销毁队列*/
Status DestroyQueue(LinkQueue* Q)
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
	}
}