#include <iostream>
#include "Population.h"
using namespace std;

int main(void)
{
	/* ��������������� ������������� */
	Population Pop(100, 0.5, 0.0, 2);


	/* ���� */
	Pop.life();

	system("pause");
	return 0;
}