# include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int QElemType;
typedef int Status;

/*�洢�ṹ*/
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;  // ��ͷָ��
	QueuePtr rear;  // ��βָ��
}LinkQueue;

/*��ʼ������*/
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front = Q->rear = NULL;
	return OK;                                                                                             
}
/*���ٶ���*/
Status DestroyQueue(LinkQueue* Q)
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
	}
}