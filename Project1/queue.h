#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "common.h"

typedef int QElemType;
typedef int Status;

/*存储结构*/
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct
{
	QueuePtr front;  // 队头指针
	QueuePtr rear;  // 队尾指针
}LinkQueue;

Status ClearQueue(LinkQueue* Q);
Status DeQueue(LinkQueue* Q, QElemType& e);
Status DestroyQueue(LinkQueue* Q);
Status EnQueue(LinkQueue* Q, QElemType e);
Status GetQueueHead(LinkQueue Q, QElemType& e);
int GetQueueLength(LinkQueue Q);
Status InitQueue(LinkQueue* Q);
Status IsQueueEmpty(LinkQueue Q);
int TestQueue();
Status TraverseQueue(LinkQueue Q, void(*visit)(QElemType));
void VisitQueue(QElemType e);
int TestQueue();
void TestStdQueue();
#endif
