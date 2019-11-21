
#include <iostream>

#include"linear_list.h"
#include "linear_list_apply.h"
using namespace std;

class A
{
public:
	A() {};
	A(int num) { this->num = num; };
	void test();
private:
	int num;
};
class B
{
	public:
	void test();
};

void A::test()
{
	cout << "class A test()" << num<< endl;
}
void B::test()
{
	cout << "class B test()" << endl;
}

int main()
{

	unionFindWithArray test;
	test.testMain();


	system("pause");
	return 0;
}


