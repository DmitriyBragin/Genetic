#include "Selection.h"
#include <iostream>

int* Selection::rouletteSelection()
{
	/* �������� �� ������ ������� � ������� �� ������������ */
	Roulette R(Pop);
	parent[0] = R.spinRoulette();
	parent[1] = R.spinRoulette();
	while ((parent[0] == parent[1]))
	{
		parent[1] = R.spinRoulette();
	}
	return parent;
}

int* Selection::tournamentSelection()
{
	/* ��������� �������� � ������� �� ������������ */
	Tournament T(Pop);
	parent = T.determineWinner();
	return parent;
}

int* Selection::panmixedSelection()
{
	/* ��������� � ������� �� ������������ */
	parent[0] = rand() % sizePopulation;
	parent[1] = rand() % sizePopulation;
	while ((parent[0] == parent[1]))
	{
			parent[1] = rand() % sizePopulation;
	}
	return parent;
}

int* Selection::inbreedSelection()
{
	int firstParent = rand() % sizePopulation;
	int secondParent = 0;
	if (firstParent == 0)
		secondParent = 1;
	else if (firstParent == sizePopulation - 1)
		secondParent = sizePopulation - 2;
	else secondParent = firstParent + 1;
	parent[0] = firstParent;
	parent[1] = secondParent;
	return parent;

}