#ifndef __SORT_H
#define __SORT_H

#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/***********实现堆排序************************
* 简介：堆排序是一种选择排序，它的最坏，最好，平均时间复杂度均为O(nlogn)，它也是不稳定排序
* 主要思路:
	第一步，构建初始堆，一般升序采用大顶推，降序采用小顶堆
	第二步：将堆顶元素与末尾元素进行交换，使末尾元素最大。然后继续调整堆，使得新的堆顶元素为第二大元素，再与末尾元素交换位置，如此反复
	Tips：这里注意第二步中数组的长度要相应发生变化，即最后已排序的部分不参与堆重建。

* 函数说明：
	void heapSort(int arr[], int size)
		输入参数：数组名，数组长度
		输出：排序好的数组，本例中是升序排列

	void adjust(int arr[], int len, int index)
		输入参数：数组名，数组长度，非叶节点对应的数组下标
		输出：该节点处存储的是以该节点为父节点所有节点值的最大值

	int main_test()
		测试用的main函数

* 算法图解过程参考：https://www.cnblogs.com/chengxiao/p/6129630.html
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
	if (right<len && arr[right] > arr[maxIdx]) maxIdx = right;  // maxIdx是3个数中最大数的下标
	if (maxIdx != index)                 // 如果maxIdx的值有更新
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);       // 递归调整其他不满足堆性质的部分
	}

}
void CHeapSort::heapSort(int arr[], int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)  // 对每一个非叶结点进行堆调整(从最后一个非叶结点开始)
	{
		adjust(arr, size, i);
	}
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);           // 将当前最大的放置到数组末尾
		adjust(arr, i, 0);              // 将未完成排序的部分继续进行堆排序
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



