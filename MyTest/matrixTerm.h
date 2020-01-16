#ifndef matrixTerm_
#define matrixTerm_
#include "extendedArrayList.h"
// 定义结构体，存储非0项的行、列、及元素值
template <class T>
struct matrixTerm
{
	int row,
		col;
	T value;

	operator T() const { return value; }
	// type conversion from matrixTerm to T
};

#endif
