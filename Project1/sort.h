#ifndef __SORT_H
#define __SORT_H

#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/***********ʵ�ֶ�����************************
* ��飺��������һ��ѡ���������������ã�ƽ��ʱ�临�ӶȾ�ΪO(nlogn)����Ҳ�ǲ��ȶ�����
* ��Ҫ˼·:
	��һ����������ʼ�ѣ�һ��������ô��ƣ��������С����
	�ڶ��������Ѷ�Ԫ����ĩβԪ�ؽ��н�����ʹĩβԪ�����Ȼ����������ѣ�ʹ���µĶѶ�Ԫ��Ϊ�ڶ���Ԫ�أ�����ĩβԪ�ؽ���λ�ã���˷���
	Tips������ע��ڶ���������ĳ���Ҫ��Ӧ�����仯�������������Ĳ��ֲ�������ؽ���

* ����˵����
	void heapSort(int arr[], int size)
		��������������������鳤��
		���������õ����飬����������������

	void adjust(int arr[], int len, int index)
		��������������������鳤�ȣ���Ҷ�ڵ��Ӧ�������±�
		������ýڵ㴦�洢�����Ըýڵ�Ϊ���ڵ����нڵ�ֵ�����ֵ

	int main_test()
		�����õ�main����

* �㷨ͼ����̲ο���https://www.cnblogs.com/chengxiao/p/6129630.html
*/
class CHeapSort
{
public:
	//int arr[];
	//CHeapSort(int arr[]) :arr[]{};
	~CHeapSort() {};
	void adjust(int arr[], int len, int index);
	void heapSort(int arr[], int size);
	int main_test();
};

void CHeapSort::adjust(int arr[], int len, int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx]) maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx]) maxIdx = right;  // maxIdx��3��������������±�
	if (maxIdx != index)                 // ���maxIdx��ֵ�и���
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);       // �ݹ������������������ʵĲ���
	}

}
void CHeapSort::heapSort(int arr[], int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)  // ��ÿһ����Ҷ�����жѵ���(�����һ����Ҷ��㿪ʼ)
	{
		adjust(arr, size, i);
	}
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);           // ����ǰ���ķ��õ�����ĩβ
		adjust(arr, i, 0);              // ��δ�������Ĳ��ּ������ж�����
	}
}

int CHeapSort::main_test()
{
	int array[8] = { 8, 1, 14, 3, 21, 5, 7, 10 };
	heapSort(array, 8);
	for (auto it : array)
	{
		cout << it << endl;
	}
	return 0;
	}

#endif 



