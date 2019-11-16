#ifndef __ALGOSTUFF_HPP_
#define __ALGOSTUFF_HPP_
// ���������ļ�  ��׼��P517

// ������׼���㷨�г��õ�ͷ�ļ�
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>


// INSERT_ELEMENTS(collection, first, last)

// ��Ԫ�ذ����ڵ�һ��ʵ��������������ڡ�Ԫ��ֵ���Եڶ�ʵ�κ͵���ʵ�Ρ�����������Ԫ��ֵ����������֮�á�
template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
	for (int i = first; i <= last; ++i)
	{
		coll.insert(coll.end(), i);
	}
}

// ����һ��ʵ��������������ڵ�����Ԫ�ش��г���������ÿո����֡��ڶ���ʵ�ο��п��ޣ���ָ�������Ϊǰ׺��ӡ��Ԫ��ֵ֮ǰ
template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optcstr = "")
{
	std::cout << optcstr;
	for (auto elem : coll)
	{
		std::cout << elem << " ";

	}
	std::cout << std::endl;
}

// ����������������ͬ��ֻ�����������ڴ���key/value pairԪ�ص���������map��multimap��
template <typename T>
inline void PRINT_MAPPED_ELEMENTS(const T& coll, const std::string& optcstr = "")
{
	std::cout << optcstr;
	for (auto elem : coll)
	{
		std::cout << "[" << elem.first << "," << elem.second << "]";

	}
	std::cout << std::endl;
}
#endif // !__ALGOSTUFF_HPP_
