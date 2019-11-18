
#include <iostream>

#include"linear_list.h"
#include "bin_sort.h"
using namespace std;


int main()
{
	chain<studentRecord> the_chain;

	string A, B, C;
	A = "A";
	B = "B";
	C = "C";
	studentRecord student1{ &A, 3 }, student2{ &B,1 }, student3{ &C, 2 };

	chain<studentRecord> *new_chain = new chain<studentRecord>;
	new_chain->insert(0, student1);
	new_chain->insert(0, student1);
	new_chain->insert(0, student2);
	new_chain->insert(0, student3);

	the_chain.insert(0, student1);
	the_chain.insert(0, student2);
	the_chain.insert(0, student3);
	cout << "   " << *new_chain << endl;

	binSort2(*new_chain, 4);
	cout << "   " << *new_chain << endl;
	/*
	int a = 0;
	int* p = &a;
	vector <int> vec{ 1,2,4,3,2 };
	int array[10] = { 8, 1, 14, 3, 21, 5, 7, 10, 45, -11 };
	
	for (auto it : vec)
	{
		cout << it << endl;
	}
	*/
	delete new_chain;
	system("pause");
	return 0;
}


