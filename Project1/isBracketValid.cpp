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
C++�������˼·ʵ��isValid(string)�ж��ַ����Ƿ�����Ч�����Ŷԡ�
1. ���Ŷ��ǿɳ�ʼ��(init)�������(addParentheses)�ģ�
2. �����Ž��б��룬�����ű���Ϊn���������ű���Ϊ-n��
3. ����ջ��һ���ݽṹ�����ԣ��жϵ�ǰ�ַ���ջ���ַ��Ƿ���ԡ�
*/
class Solution {
public:
	// ��Ϊ���ύƽ̨���ԣ�������ҪΪ���캯���ṩ���Ŷ���ΪĬ�ϲ���
	Solution(string str = "(){}[]") {
		this->init(str);
	}

public:
	// C++ʵ�֣��ж��ַ���s�Ƿ�����Ч������
	bool isValid(string s) {
		std::stack<int> parenthesesEnCodeStk;
		int len = s.length();
		for (int i = 0; i < len; ++i) {
			int charEnCode = this->getCharEnCode(s[i]);
			// ���������ַ�
			if (charEnCode == 0)
				continue;

			// ������
			if (charEnCode > 0) {
				// ��ջ�������������Ѿ����ڵ��ڲ��Դ����ȵ�һ���ˣ���ʹ����ȫ����ȷ�������ţ�Ҳ������
				if (parenthesesEnCodeStk.size() >= len / 2)
					return false;

				// ��������ѹ��ջ��
				parenthesesEnCodeStk.push(charEnCode);
			}
			else {
				// ���������ʧ�ܣ���ջ�ѿգ�����ջ���������뵱ǰ�����Ų��ɶ�
				if (parenthesesEnCodeStk.empty() || charEnCode + parenthesesEnCodeStk.top() != 0)
					return false;

				// ��������Գɹ���ջ�������ŵ���ջ
				parenthesesEnCodeStk.pop();
			}
		}

		// ���ջ�ڻ��������ţ���ʾ���ʧ�ܣ���֮��
		return parenthesesEnCodeStk.empty();
	}

	// ��ʼ��
	void init(string parenthesesStr) {
		m_parenthesesEnCodeMap.clear();

		int len = parenthesesStr.length() / 2;
		for (int i = 0; i < len; ++i) {
			this->addParentheses(parenthesesStr[i * 2], parenthesesStr[i * 2 + 1]);
		}
	}

	// ������Ŷԣ�ͬʱΪ�����
	void addParentheses(char leftChar, char rightChar) {
		int nSize = m_parenthesesEnCodeMap.size();
		int nEnCode = nSize / 2 + 1;
		m_parenthesesEnCodeMap.insert(std::make_pair(leftChar, nEnCode));
		m_parenthesesEnCodeMap.insert(std::make_pair(rightChar, -nEnCode));
	}

private:
	// �������ŵı���
	int getCharEnCode(char c) {
		std::map<char, int>::iterator itFind = m_parenthesesEnCodeMap.find(c);
		if (itFind == m_parenthesesEnCodeMap.end())
			return 0;
		else
			return itFind->second;
	}

private:
	// ������ŵı���
	std::map<char, int> m_parenthesesEnCodeMap;
};
/*  ������
int main() {
	Solution slt;
	string testStr("(()){}");
	std::cout << slt.isValid(testStr);
	return 0;
}
*/


