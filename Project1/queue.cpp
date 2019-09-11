# include <iostream>
#include "queue.h"
# include <queue>
using namespace std;

/*函数说明：
* 队头指针front的下一个节点表示真正的队头节点，front是一个指向节点的指针，它的值是队头元素前一个节点的地址
* 队尾指针rrear的值是队尾节点，它的值是队尾节点的地址。
*/

/*初始化队列*/
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->rear ->next = Q->front->next = NULL;  // 三种初始化都可以？？？ Q->front->next = NULL;  Q->rear ->next = NULL;
	return OK;                                                                                             
}
/*销毁队列*/
Status DestroyQueue(LinkQueue* Q)
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

/*清空队列
* 先销毁队列，此时队列不再存在，然后初始化，此时队列为空
*/
Status ClearQueue(LinkQueue* Q)
{
	DestroyQueue(Q);
	InitQueue(Q);
	return OK;
}

/*判断队列是否为空*/
Status IsQueueEmpty(LinkQueue Q)
{
	if (Q.front->next == NULL)  // 当首尾指向相同时是否是空？
		return TRUE;
	else
		return FALSE;
}

/*获取队列的长度*/
int GetQueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p = Q.front;
	while (Q.rear != p)
	{
		++i;
		p = p->next;
	}
	return i;
}

/*获取对头元素*/
Status GetQueueHead(LinkQueue Q, QElemType& e)
{
	if (Q.front->next == NULL)
	{
		cout << "empty  queue" << endl;
		return ERROR;
	}
	else
		e = (Q.front->next)->data;
	return OK;
}

/*入队*/
Status EnQueue(LinkQueue* Q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		exit(OVERFLOW);
		cout << "分配内存失败" << endl;
	}
	p->data = e;
	p->next = NULL;

	Q->rear->next = p;  // 将p转换为新的队尾元素
	Q->rear = p;  // 将指针指向队尾元素
	return OK;

}

/*出队*/
Status DeQueue(LinkQueue* Q, QElemType &e)
{
	if (Q->front == Q->rear)
		return ERROR;
	QueuePtr temp;	
	temp = Q->front->next;
	e = temp->data;
	
	Q->front->next = temp->next;
	if (Q->rear == temp)
		Q->rear = Q->front;
	free(temp);
	return OK;
}

/*访问元素*/
void VisitQueue(QElemType e)
{
	cout << dec << e << endl;
}

/*遍历队列*/
Status TraverseQueue(LinkQueue Q, void(*visit)(QElemType))
{
	QueuePtr p = Q.front->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	return OK;
}

int TestQueue()
{
	LinkQueue Q;
	if (InitQueue(&Q))
	{
		QElemType e;
		
		cout << "init_success" << endl;
		if (IsQueueEmpty)
			cout << "Queue is empty" << endl;
		for (int i = 0; i < 10; ++i)
		{
			EnQueue(&Q, i);
		}
		cout << "入队完毕" << endl;
		GetQueueHead(Q, e);
		cout << "the head element is : " << e << endl;
		cout << "length is :" << GetQueueLength(Q) << endl;

		DeQueue(&Q, e);
		TraverseQueue(Q, *VisitQueue);
		cout << "delete element is : " << e << endl;
		
		if(DestroyQueue(&Q))
			cout <<"destroy success"<<endl;


	}
	return 0;
}

void TestStdQueue()
{
	std::queue<int> q;
	cout << "is q empty?" << q.empty() << endl;

	for (int i = 0; i < 10; ++i)
		q.push(i);

	cout << "the length of q : " << q.size() << endl;

	cout << "the front element is : " << q.front() << endl;

	cout << "the last element is : " << q.back() << endl;

	q.pop();
	cout << "the front element after 1 pop is : " << q.front() << endl;
}