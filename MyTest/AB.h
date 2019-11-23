#include <iostream>
using namespace std;
class A
{
	friend ostream& operator<< (ostream& outA, const A& x);
public:
	A() {};
	A(int a) { this->a = a; };
	int operator+(const A& x)
	{
		return x.a + a;
	}
	int operator+(int x)
	{
		return x + a;
	}
	int returna()
	{
		return a;
	}

private:
	int a;
};
ostream& operator<< (ostream& outA, const A& x)
{
	outA << "this class A " << x.a;
	return outA;
}

class B
{
	friend ostream& operator<< (ostream& outB, const B& x);
public:
	B() {};
	B(int b) { this->b = b; };
	int operator+(const B& x)
	{
		return x.b + b;
	}
	int operator+(int x)
	{
		return x + b;
	}


private:
	int b;
};
ostream& operator<< (ostream& outB, const B& x)
{
	outB << "this class B " << x.b;
	return outB;
}
#pragma once
