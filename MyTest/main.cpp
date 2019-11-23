
#include <iostream>
#include <sstream>

#include "arrayAndMatrix.h"
#include <string>
using std::string;
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

int main()
{
	A a(2);
	B b(4);
	matrix<int> m(1, 1);
	m(1, 1) = 4;
	cout << a << endl;
	cout << b << endl;
	cout << m << endl;
	testMain();
	system("pause");
	return 0;
}


