#include <iostream>
#include "Population.h"
using namespace std;

int main(void)
{
	/* Предварительные приготовления */
	Population Pop(40, 0.5, 0.0, 2);


	/* Цикл */
	Pop.life();

	system("pause");
	return 0;
}