#ifndef matrixTerm_
#define matrixTerm_
#include "extendedArrayList.h"
// ����ṹ�壬�洢��0����С��С���Ԫ��ֵ
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
