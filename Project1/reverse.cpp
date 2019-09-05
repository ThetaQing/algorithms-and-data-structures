#include <iostream>
/*******************************
* 函数名称：reverse(int x)
* 函数参数：int x
* 函数返回值：int类型，返回输入变量x的翻转值
* 函数实现思路：利用取余，依次得到取余后的数然后组合起来
* 函数注意点：注意判断溢出的方法，INT_MAX = 2147483648；INT_MIN = 2147483647
*/
int reverse(int x) {
	int temp = 0;  // 临时变量，存储余数
	int result = 0;  // 存储最终结果
	while (x)
	{
		temp = x % 10;  // 取余
		x = x / 10;  // 得到下一步要处理的x

		if (result > INT_MAX / 10 || (result == INT_MAX / 10 && x % 10 > 7))  // 判断是否超出最大值
			return 0;
		if (result < INT_MIN / 10 || (result == INT_MIN / 10 && x % 10 < -8))  // 判断是否超出最小值
			return 0;
		result = result * 10 + temp;  // 如果没有超出，得到这一轮翻转后的结果。
	}


	return result;
}