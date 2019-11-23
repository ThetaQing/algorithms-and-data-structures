
#include <iostream>
#include <sstream>
#include "test.h"
//#include "arrayAndMatrix.h"
using namespace std;

class score
{
	//friend ostream& operator<< (ostream&, const score&);
public:
	score() {};
	score(string name, int sco)
	{
		this->theName = name;
		this->theScore = sco;
	}
	~score() {};
	int countScore()
	{
		return theScore;
	}
	string name()
	{
		return theName;
	}
	void ouput(ostream& out)const
	{
		out << theName << "  " << theScore << "   ";
	}
	int add(score x)
	{
		return x.countScore() + theScore;
	}
	int operator+(const int &x)
	{
		return theScore + x;
	}
private:
	string theName;
	int theScore;
};

/*
ostream& operator <<(ostream& os, const score &student)
{
	os << student.theName << "   " << student.theScore;
	os << endl;
	return os;
	//os << student.name() << " " << student.countScore();
}*/

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
	/*ostream& operator<< (ostream& outA)
	{
		outA << "this class A " << a;
		return outA;
	}*/
private:
	int a;
};
ostream& operator<< (ostream& outA, const A & x)
{
	outA << "this class A " << x.a;
	return outA;
}

class B
{
	friend ostream& operator<< (ostream& outA, const B& x);
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

ostream& operator<< (ostream& outB,const B& x)
{
	outB << "this class B " << x.b;
	return outB;
}
int main()
{
	
	A a1(3), a2(4);
	B b1(5), b2(6);
	C c1(7), c2(8);
	int a = a1 + 4;
	int b = b1 + 5;
	int c = c1 + 9;
	cout << a << "    " << b << "    " <<  c << endl;
	cout << a1;
	cout << b1;
	//cout << b1;
	system("pause");
	return 0;
}


