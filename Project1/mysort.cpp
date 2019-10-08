
#include <iostream>
using namespace std;

/************快速排序*****************
* 函数名：Qsort(int arr[], int low, int high)
* 输入值：int arr[], int low, int high分别表示输入数组，数组下限，数组上限
* 返回值：通过地址传递，返回排序完成的数组
*/

void Qsort(int arr[], int low, int high) {
	if (high <= low) return;
	int i = low;
	int j = high + 1;
	int key = arr[low];
	while (true)
	{
		/*从左向右找比key大的值*/
		while (arr[++i] < key)
		{
			if (i == high) {
				break;
			}
		}
		/*从右向左找比key小的值*/
		while (arr[--j] > key)
		{
			if (j == low) {
				break;
			}
		}
		if (i >= j) break;
		/*交换i,j对应的值*/
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	/*中枢值与j对应值交换*/
	int temp = arr[low];
	arr[low] = arr[j];
	arr[j] = temp;
	Qsort(arr, low, j - 1);
	Qsort(arr, j + 1, high);
}

/**************归并排序算法****************
* 函数名：void Merge(int* a, int p, int q, int r)；
* 输入值：int* a, int p, int q, int r分别表示输入数组，p,q,r分别表示数组下标
* 返回值：地址传参形式，返回合并的数组
* 函数功能：实现对两个有序数组的合并
*/

void Merge(int* a, int p, int q, int r)
{
	int n1 = q - p + 1;       //左部分的的元素个数
	int n2 = r - q;           //同上
	int i, j, k;
	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];
	for (i = 0; i < n1; i++)
		L[i] = a[p + i];
	for (j = 0; j < n2; j++)
		R[j] = a[q + j + 1];
	L[n1] = 11111111;
	R[n2] = 11111111;
	// 数组L从0~n1-1存放，第n1个存放int型所能表示的最大数，即认为正无穷，这是为了
	//处理合并时，比如当数组L中的n1个元素已经全部按顺序存进数组a中，只剩下数组R的
	//部分元素，这时因为R中剩下的元素全部小于11111111,则执行else语句，直接将剩下的
	//元素拷贝进a中。
	for (i = 0, j = 0, k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
			a[k] = L[i++];
		else
			a[k] = R[j++];
	}

	delete[]L;
	delete[]R;
}
/*归并排序实现
* 函数名：void MergeSort(int* a, int l, int r)
* 函数参数：int* a, int l, int r，分别表示数组下标
* 函数返回值：地址传参，返回排好序的数组
* 函数功能：实现将数组分解为单个数组单元，然后调用归并函数，对数组进行排序。
*/
void MergeSort(int* a, int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		MergeSort(a, l, m);
		MergeSort(a, m + 1, r);
		Merge(a, l, m, r);
	}
	
}

