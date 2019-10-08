
#include <iostream>
using namespace std;

/************��������*****************
* ��������Qsort(int arr[], int low, int high)
* ����ֵ��int arr[], int low, int high�ֱ��ʾ�������飬�������ޣ���������
* ����ֵ��ͨ����ַ���ݣ�����������ɵ�����
*/

void Qsort(int arr[], int low, int high) {
	if (high <= low) return;
	int i = low;
	int j = high + 1;
	int key = arr[low];
	while (true)
	{
		/*���������ұ�key���ֵ*/
		while (arr[++i] < key)
		{
			if (i == high) {
				break;
			}
		}
		/*���������ұ�keyС��ֵ*/
		while (arr[--j] > key)
		{
			if (j == low) {
				break;
			}
		}
		if (i >= j) break;
		/*����i,j��Ӧ��ֵ*/
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	/*����ֵ��j��Ӧֵ����*/
	int temp = arr[low];
	arr[low] = arr[j];
	arr[j] = temp;
	Qsort(arr, low, j - 1);
	Qsort(arr, j + 1, high);
}

/**************�鲢�����㷨****************
* ��������void Merge(int* a, int p, int q, int r)��
* ����ֵ��int* a, int p, int q, int r�ֱ��ʾ�������飬p,q,r�ֱ��ʾ�����±�
* ����ֵ����ַ������ʽ�����غϲ�������
* �������ܣ�ʵ�ֶ�������������ĺϲ�
*/

void Merge(int* a, int p, int q, int r)
{
	int n1 = q - p + 1;       //�󲿷ֵĵ�Ԫ�ظ���
	int n2 = r - q;           //ͬ��
	int i, j, k;
	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];
	for (i = 0; i < n1; i++)
		L[i] = a[p + i];
	for (j = 0; j < n2; j++)
		R[j] = a[q + j + 1];
	L[n1] = 11111111;
	R[n2] = 11111111;
	// ����L��0~n1-1��ţ���n1�����int�����ܱ�ʾ�������������Ϊ���������Ϊ��
	//����ϲ�ʱ�����統����L�е�n1��Ԫ���Ѿ�ȫ����˳��������a�У�ֻʣ������R��
	//����Ԫ�أ���ʱ��ΪR��ʣ�µ�Ԫ��ȫ��С��11111111,��ִ��else��䣬ֱ�ӽ�ʣ�µ�
	//Ԫ�ؿ�����a�С�
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
/*�鲢����ʵ��
* ��������void MergeSort(int* a, int l, int r)
* ����������int* a, int l, int r���ֱ��ʾ�����±�
* ��������ֵ����ַ���Σ������ź��������
* �������ܣ�ʵ�ֽ�����ֽ�Ϊ�������鵥Ԫ��Ȼ����ù鲢�������������������
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

