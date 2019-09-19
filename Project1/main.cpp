# include <iostream>
# include <string>
# include ".\common.h"
# include "linklist.h"
#include ".\LeetCode\labfile.h"
# include ".\LeetCode\LeetCode.h"
# include "stack.h"
# include "binarytree.h"
# include <vector>
# include <typeinfo>
# include ".\LeetCode\LeetCode.h"
#include <algorithm>
#include <stdio.h>
#include "mysort.h"

using std::vector;
using namespace std;

using std::string;
#define N 7
int fun1(char s[], char a, int n)
{
	int j;
	j = n;
	while (a < s[j] && j > 0)
		j--;
	return j;
}
int fun2(char s[], char a, int n)
{
	int j;
	j = 1;
	while (a > s[j] && j <= n)
		j++;
	return j;
}


int main()
{
	int a[] = { 57, 68, 59, 52, 72, 28, 96, 33, 24 };
	int b = 0;
	int* p = &b;
	cout << *(a+1) << endl;
	cout << sizeof(a) << endl;
	return 0;
	system("pause");
}

