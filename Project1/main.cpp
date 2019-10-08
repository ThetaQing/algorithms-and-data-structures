#include "sort.h"
#include <iostream>



using namespace std;

int main()
{
	
	int array[10] = { 8, 1, 14, 3, 21, 5, 7, 10, 45, -11 };
	CHeapSort test;
	test.heapSort(array, 10);
	for (auto it : array)
	{
		cout << it << endl;
	}
	return 0;
}