# include <iostream>
# include <vector>
# include <algorithm>
using std::vector;
using namespace std;

/*
* 问题描述：输入一组整数，求出这组数字子序列和中的最大值，只要求出最大子序列的和，不要求最大值对应的序列。
*/
int Lab_max_sub(vector<int> input_list)
{
	
	int temp = 0;
	int sum = 0;
	vector<int> sum_max;	
	for (auto value : input_list)
	{		
		sum = sum + value;
		if (temp < sum)
		{
			temp = sum;
			sum_max.push_back(sum);
			cout << sum << endl;
			
		}
	}

	auto max = max_element(sum_max.begin(), sum_max.end());
	return *max;

}