// test bin sort as member of chain class

#include <iostream>
#include "studentRecord2.h"
#include "chainWithBinSort.h"
/**************
* 注释原因：测试Project1中箱子排序的主函数
int main(void)
{
   studentRecord s;
   chain<studentRecord> theChain;
   for (int i = 1; i <= 20; i++)
   {
      s.score = i/2;
      s.name = new string(s.score, 'a');
      theChain.insert(0,s);
   }
   cout << "The unsorted chain is" << endl;
   cout << "  " << theChain << endl;
   theChain.binSort(10);
   cout << "The sorted chain is" << endl;
   cout << "  " << theChain << endl;
}*/
void testBinSort()
{
	chain<studentRecord> the_chain;

	string A, B, C;
	A = "A";
	B = "B";
	C = "C";
	studentRecord student1, student2, student3;
	student1.name = &A;
	student1.score = 2;
	student2.name = &B;
	student2.score = 1;
	student3.name = &C;
	student3.score = 3;


	the_chain.insert(0, student1);
	the_chain.insert(0, student2);
	the_chain.insert(0, student3);
	//the_chain.output(*out);
	cout << "  " << the_chain << endl;
	the_chain.binSort(4);
	cout << "  " << the_chain << endl;
	//the_chain.output(*out);
}

int main()
{

	testBinSort();
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
	system("pause");
	return 0;
}