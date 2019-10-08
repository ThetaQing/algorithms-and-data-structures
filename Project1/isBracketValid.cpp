# include <iostream>
# include <stack>
# include ".\common.h"
# include "linklist.h"
#include ".\LeetCode\labfile.h"
# include ".\LeetCode\LeetCode.h"
# include "binarytree.h"
# include <vector>
# include <map>
# include ".\LeetCode\LeetCode.h"
#include <algorithm>
#include <stdio.h>
#include "mysort.h"

using std::vector;
using namespace std;

using std::stack;




/*
C++面向对象思路实现isValid(string)判断字符串是否是有效的括号对。
1. 括号对是可初始化(init)，可添加(addParentheses)的；
2. 将括号进行编码，左括号编码为n，则右括号编码为-n；
3. 利用栈这一数据结构的特性，判断当前字符和栈顶字符是否配对。
*/
class Solution {
public:
	// 因为是提交平台测试，所以需要为构造函数提供括号对作为默认参数
	Solution(string str = "(){}[]") {
		this->init(str);
	}

public:
	// C++实现：判断字符串s是否是有效的括号
	bool isValid(string s) {
		std::stack<int> parenthesesEnCodeStk;
		int len = s.length();
		for (int i = 0; i < len; ++i) {
			int charEnCode = this->getCharEnCode(s[i]);
			// 忽略其它字符
			if (charEnCode == 0)
				continue;

			// 左括号
			if (charEnCode > 0) {
				// 若栈内左括号数量已经大于等于测试串长度的一半了，即使后面全是正确的右括号，也不够了
				if (parenthesesEnCodeStk.size() >= len / 2)
					return false;

				// 将左括号压入栈顶
				parenthesesEnCodeStk.push(charEnCode);
			}
			else {
				// 右括号配对失败：堆栈已空，或者栈顶左括号与当前右括号不成对
				if (parenthesesEnCodeStk.empty() || charEnCode + parenthesesEnCodeStk.top() != 0)
					return false;

				// 右括号配对成功，栈顶左括号弹出栈
				parenthesesEnCodeStk.pop();
			}
		}

		// 如果栈内还有左括号，表示配对失败；反之。
		return parenthesesEnCodeStk.empty();
	}

	// 初始化
	void init(string parenthesesStr) {
		m_parenthesesEnCodeMap.clear();

		int len = parenthesesStr.length() / 2;
		for (int i = 0; i < len; ++i) {
			this->addParentheses(parenthesesStr[i * 2], parenthesesStr[i * 2 + 1]);
		}
	}

	// 添加括号对，同时为其编码
	void addParentheses(char leftChar, char rightChar) {
		int nSize = m_parenthesesEnCodeMap.size();
		int nEnCode = nSize / 2 + 1;
		m_parenthesesEnCodeMap.insert(std::make_pair(leftChar, nEnCode));
		m_parenthesesEnCodeMap.insert(std::make_pair(rightChar, -nEnCode));
	}

private:
	// 查找括号的编码
	int getCharEnCode(char c) {
		std::map<char, int>::iterator itFind = m_parenthesesEnCodeMap.find(c);
		if (itFind == m_parenthesesEnCodeMap.end())
			return 0;
		else
			return itFind->second;
	}

private:
	// 存放括号的编码
	std::map<char, int> m_parenthesesEnCodeMap;
};
/*  主函数
int main() {
	Solution slt;
	string testStr("(()){}");
	std::cout << slt.isValid(testStr);
	return 0;
}
*/


