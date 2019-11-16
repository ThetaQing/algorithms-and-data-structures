#ifndef __ALGOSTUFF_HPP_
#define __ALGOSTUFF_HPP_
// 辅助函数文件  标准库P517

// 包含标准库算法中常用的头文件
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

// 将元素安插于第一个实参所引入的容器内。元素值来自第二实参和第三实参——其间的所有元素值都将供安插之用。
template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
	for (int i = first; i <= last; ++i)
	{
		coll.insert(coll.end(), i);
	}
}

// 将第一个实参所引入的容器内的所有元素打列出来，其间用空格区分。第二个实参可有可无，若指定将会成为前缀打印于元素值之前
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

// 和上述函数功能相同，只不过它适用于带有key/value pair元素的容器，如map、multimap等
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
