
#include <iostream>
#include <sstream>
#include "AB.h"
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


