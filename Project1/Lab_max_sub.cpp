# include <iostream>
# include <vector>
# include <algorithm>
using std::vector;
using namespace std;

/*
* ��������������һ������������������������к��е����ֵ��ֻҪ�����������еĺͣ���Ҫ�����ֵ��Ӧ�����С�
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