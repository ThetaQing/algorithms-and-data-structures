# include <iostream>
#include "queue.h"
# include <queue>
using namespace std;

/*����˵����
* ��ͷָ��front����һ���ڵ��ʾ�����Ķ�ͷ�ڵ㣬front��һ��ָ��ڵ��ָ�룬����ֵ�Ƕ�ͷԪ��ǰһ���ڵ�ĵ�ַ
* ��βָ��rrear��ֵ�Ƕ�β�ڵ㣬����ֵ�Ƕ�β�ڵ�ĵ�ַ��
*/

/*��ʼ������*/
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->rear ->next = Q->front->next = NULL;  // ���ֳ�ʼ�������ԣ����� Q->front->next = NULL;  Q->rear ->next = NULL;
	return OK;                                                                                             
}
/*���ٶ���*/
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

/*��ն���
* �����ٶ��У���ʱ���в��ٴ��ڣ�Ȼ���ʼ������ʱ����Ϊ��
*/
Status ClearQueue(LinkQueue* Q)
{
	DestroyQueue(Q);
	InitQueue(Q);
	return OK;
}

/*�ж϶����Ƿ�Ϊ��*/
Status IsQueueEmpty(LinkQueue Q)
{
	if (Q.front->next == NULL)  // ����βָ����ͬʱ�Ƿ��ǿգ�
		return TRUE;
	else
		return FALSE;
}

/*��ȡ���еĳ���*/
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

/*��ȡ��ͷԪ��*/
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

/*���*/
Status EnQueue(LinkQueue* Q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		exit(OVERFLOW);
		cout << "�����ڴ�ʧ��" << endl;
	}
	p->data = e;
	p->next = NULL;

	Q->rear->next = p;  // ��pת��Ϊ�µĶ�βԪ��
	Q->rear = p;  // ��ָ��ָ���βԪ��
	return OK;

}

/*����*/
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

/*����Ԫ��*/
void VisitQueue(QElemType e)
{
	cout << dec << e << endl;
}

/*��������*/
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
		cout << "������" << endl;
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