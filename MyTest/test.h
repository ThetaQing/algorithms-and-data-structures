#ifndef __TEST_H__
#define __TEST_H__

class C
{
	friend ostream& operator<< (ostream& outC, C& x);
public:
	C() {};
	C(int a)
	{
		this->a = a;
	}
	int operator+(const C& x)
	{
		return x.a + a;
	}
	int operator+(int x)
	{
		return x + a;
	}
	
	
private:
	int a;
};


ostream& operator<< (ostream& outB, C& x)
{
	outB << "this class C " << x.a;
	return outB;
}

#endif // !__TEST_H__



#pragma once
