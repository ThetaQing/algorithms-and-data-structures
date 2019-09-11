#include <iostream>
/*******************************
* �������ƣ�reverse(int x)
* ����������int x
* ��������ֵ��int���ͣ������������x�ķ�תֵ
* ����ʵ��˼·������ȡ�࣬���εõ�ȡ������Ȼ���������
* ����ע��㣺ע���ж�����ķ�����INT_MAX = 2147483648��INT_MIN = 2147483647
*/
int reverse(int x) {
	int temp = 0;  // ��ʱ�������洢����
	int result = 0;  // �洢���ս��
	while (x)
	{
		temp = x % 10;  // ȡ��
		x = x / 10;  // �õ���һ��Ҫ�����x

		if (result > INT_MAX / 10 || (result == INT_MAX / 10 && x % 10 > 7))  // �ж��Ƿ񳬳����ֵ
			return 0;
		if (result < INT_MIN / 10 || (result == INT_MIN / 10 && x % 10 < -8))  // �ж��Ƿ񳬳���Сֵ
			return 0;
		result = result * 10 + temp;  // ���û�г������õ���һ�ַ�ת��Ľ����
	}


	return result;
}