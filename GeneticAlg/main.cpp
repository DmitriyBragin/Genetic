#include <iostream>
#include "Population.h"
using namespace std;

int main(void)
{
	/* Предварительные приготовления */
	Population Pop(1000, 0.5, 2);


	/* Цикл */
	Pop.life();

	system("pause");
	return 0;
}