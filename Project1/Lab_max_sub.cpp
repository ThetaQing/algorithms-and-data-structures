# include <iostream>
# include <vector>
# include <algorithm>
using std::vector;
using namespace std;

/*
* ��������������һ������������������������к��е����ֵ��ֻҪ�����������еĺͣ���Ҫ�����ֵ��Ӧ�����С�
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
	// �����������
	 

	// �洢���ֵ����ʼ��Ϊarr[0]
	int max = arr[0];


	// ��ʱ�������洢������֮��
	int tempSum = 0;

	// ����Ĵ�С
	auto sizeofArr = arr.size();

	// �����зֱ��ÿ��Ԫ�ؿ�ʼ
	for (auto i = 0; i < sizeofArr; ++i)
	{
		tempSum = 0;
		// ��ͬ��β��������
		for (auto j = i; j < sizeofArr; ++j)
		{
			tempSum += arr[j];
			// �жϺ��Ƿ����max
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