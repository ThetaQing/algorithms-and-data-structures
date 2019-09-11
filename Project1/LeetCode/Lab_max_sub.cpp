# include <iostream>
# include <vector>
# include <algorithm>
using std::vector;
using namespace std;

/*
* 问题描述：输入一组整数，求出这组数字子序列和中的最大值，只要求出最大子序列的和，不要求最大值对应的序列。
*/
int LabMaxSub(vector<int> input_list)
{
	
	int temp = 0;
	int sum = 0;
	
	for (auto i = 0; i < input_list.size(); ++i)
	{		
		temp = input_list[i];
		for (auto j = i + 1; j < input_list.size(); ++j)
		{
			temp = temp + input_list[j];
			if (temp > sum)
				sum = temp;

		}
	}


	return sum;

}

int LabMain(vector<int> arr)
{
	// 定义这个序列
	 

	// 存储最大值，初始化为arr[0]
	int max = arr[0];


	// 临时变量，存储子序列之和
	int tempSum = 0;

	// 数组的大小
	auto sizeofArr = arr.size();

	// 子序列分别从每个元素开始
	for (auto i = 0; i < sizeofArr; ++i)
	{
		tempSum = 0;
		// 不同结尾的子序列
		for (auto j = i; j < sizeofArr; ++j)
		{
			tempSum += arr[j];
			// 判断和是否大于max
			if (tempSum > max)
				max = tempSum;
		}
	}
	cout << max << endl;
	return max;
}

vector<int> GenVector()
{
	vector <int> input;
	int temp;
	while (cin >> temp)
		input.push_back(temp);
	return input;
}