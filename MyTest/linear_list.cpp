#include <iostream>
#include "linear_list.h"
#include "linear_list_apply.h"
using namespace std;


/****************�ļ�˵��*****************
* �ļ�����linear_list.cpp
* �������ͣ����Ա�Ҳ�����������ÿһ��ʵ������Ԫ�ص�һ�����򼯺ϡ�
* �ļ����ܣ�ʵ�� ���塢���� ���Ա�
* ��Ҫ֪ʶ�㣺
	1�������ࣺ�����д��麯�����࣬������������������ģ����ܱ�ʵ�����������󣬶���Ҫ���鹹��������Ϊ�麯����
	2������Ҳ��ָ�룬ÿһ���ڵ㶼��ȷ������һ����ؽڵ��λ����Ϣ��


**/

void testBinSort()
{
	chain<studentRecord> the_chain;
	
	string A, B, C;
	A = "A";
	B = "B";
	C = "C";
	studentRecord student1{ &A, 3 }, student2{ &B,1 }, student3{&C, 2};  // ��������
	
	

	the_chain.insert(0, student1);
	the_chain.insert(0, student2);
	the_chain.insert(0, student3);
	
	cout << "  " << the_chain << endl;
	the_chain.binSort(4);  // �����������������ֵ
	cout << "  " << the_chain<< endl;
	
}
