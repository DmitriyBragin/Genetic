#include "Population.h"
#include "Roulette.h"
#include "Element.h"
#include "Crossover.h"
#include "Tournament.h"
#include "Selection.h"
#include "Elimination.h"
#include <iostream>

#define NAN 100.0

void Population::allocations()
{
	sizeExpandedPopulation = sizePopulation * 1.5; /* THIS COEFF IS AIDS */
	MainPopulation = new Element[sizeExpandedPopulation]; /* CAREFUL HERE */

	for (int i = 0; i < sizeExpandedPopulation; i++)
	{
		MainPopulation[i].setSize(spaceSize);
		MainPopulation[i].setRoulettePercent(0.0);
		MainPopulation[i].setTournamentStatus(true);
		MainPopulation[i].allocateData();
		double *tempArray = new double[spaceSize];
		for (int j = 0; j < spaceSize; j++)
		{
			tempArray[j] = NAN; /* THIS! */
		}
		MainPopulation[i].setData(tempArray); /* THIS ALSO */
	}
}
void Population::deleteChildren()
{
	double *temp = new double[spaceSize];
	temp[0] = NAN;
	temp[1] = NAN;
	for (int i = sizePopulation; i < sizeExpandedPopulation; i++)
	{
		MainPopulation[i].setData(temp);
	}
}

int* Population::selection()
{
	int *parent = new int[spaceSize];
	//printPopulation();
	Selection S(*this);
	//printPopulation();
	/* �������� �� ������ ������� � ������� �� ������������ */
	//parent = S.rouletteSelection(); // �������� � �� 40
	/* ��������� �������� � ������� �� ������������ */
	//parent = S.tournamentSelection(); // �� 100 �������
	/* ��������� �������� */
	//parent = S.panmixedSelection(); // �� 100 �������
	/* ��������� */
	parent = S.inbreedSelection(); // �� �������� �� 100, ������� �� 1000
	/* ���������� */
	//parent = S.outbreedSelection();
	//std::cout << "Parents: " << parent[0] + 1<< "++" << parent[1] + 1 << std::endl;
	//printPopulation();
	return parent;
}

void Population::crossoverPopulation()
{
	sortPopulation();
	//printPopulation();
	setTournamentStatus(true);
	//printPopulation();
	for (int i = sizePopulation; i < sizeExpandedPopulation; i++)
	{
		/* ����� ��������� */
		int* parents = selection();
		/* ������������ */
		Element Mother = MainPopulation[parents[0]];
		Element Father = MainPopulation[parents[1]];
		Crossover C(Mother, Father);
		Element Child = C.recombination();
		MainPopulation[i].setData(Child.getData());
		setTournamentStatus(false);
	}
}

void Population::printPopulation()
{
	for (int i = 0; i < sizePopulation; i++)
	{
		std::cout << "Element [" << i << "]:";
		MainPopulation[i].printElement();
	}
	std::cout << "______________________________________________________________" << std::endl;
}
void Population::printOptimum()
{
	std::cout << "Number of iterations: " << lifeTime << std::endl;
	std::cout << "Optimum: ";
	MainPopulation[0].printElement();
}
void Population::printExpandedPopulation()
{
	for (int i = 0; i < sizeExpandedPopulation; i++)
	{
		std::cout << "Element [" << i << "]:";
		MainPopulation[i].printElement();
	}
	std::cout << "______________________________________________________________" << std::endl;
}

void Population::printFitness()
{
	std::cout << MainPopulation[0].fitnessFunction() << std::endl;

}
void Population::generatePopulation()
{
	for (int i = 0; i < sizePopulation; i++)
	{
		double *coords = new double[spaceSize];
		for (int j = 0; j < spaceSize; j++)
		{
			coords[j] = (double)(rand()) / RAND_MAX * 100.0 - 50.0;
		}
		MainPopulation[i].setData(coords);
	}
}

void Population::sortPopulation()
{
	for (int i = 0; i < sizeExpandedPopulation - 1; i++)
	{
		for (int j = 0; j < sizeExpandedPopulation - i - 1; j++)
		{
			if (MainPopulation[j].fitnessFunction() > MainPopulation[j+1].fitnessFunction())
			{
				MainPopulation[j].swapElements(MainPopulation[j + 1]);
			}
		}
	}
}

void Population::sortParents()
{
	for (int i = 0; i < sizePopulation - 1; i++)
	{
		for (int j = 0; j < sizePopulation - i - 1; j++)
		{
			if (MainPopulation[j].fitnessFunction() > MainPopulation[j + 1].fitnessFunction())
			{
				MainPopulation[j].swapElements(MainPopulation[j + 1]);
			}
		}
	}
}

void Population::sortChilds()
{
	int k = 0;
	for (int i = sizePopulation; i < sizeExpandedPopulation - 1; i++)
	{
		for (int j = sizePopulation; j < sizeExpandedPopulation - k - 1; j++)
		{
			if (MainPopulation[j].fitnessFunction() > MainPopulation[j + 1].fitnessFunction())
			{
				MainPopulation[j].swapElements(MainPopulation[j + 1]);
			}
		}
		k++;
	}
}



Element Population::getElement(int index)
{
	return MainPopulation[index];
}

void Population::pushElement(Element a, int index)
{
	MainPopulation[index].setData(a.getData());
	MainPopulation[index].setSize(a.getSize());
	MainPopulation[index].setRoulettePercent(a.getRoulettePercent());
	MainPopulation[index].setTournamentStatus(a.getTournamentStatus());
}

int Population::mutationPopulation()
{
	int mutations = 0;
	for (int i = 0; i < sizeExpandedPopulation; i++)
	{
		if ((double)(rand()) / RAND_MAX * 100.0 < mutationCoeff)
		{
			double *coords = new double[spaceSize];
			for (int j = 0; j < MainPopulation[i].getSize(); j++)
			{
				coords[j] = (double)(rand()) / RAND_MAX * 100.0 - 50.0;
				MainPopulation[i].setData(coords);
			}
			mutations++;

		}
	}
	return mutations;
}

void Population::eliminationPopulation()
{
	Elimination E(*this);
	//E.eliteElimination(); // ������� ����������
	//E.truncateElimination();
	E.exclusionElimination();
	//printPopulation();
}

void Population::shufflePopulation()
{
	for (int i = 0; i < sizePopulation; i++)
	{
		MainPopulation[rand() % sizePopulation].swapElements(MainPopulation[rand() % sizePopulation]);
	}
}

void Population::life()
{
	allocations();

	/* ��������� �������� � ��������� ��������� */
	generatePopulation();
	sortPopulation();
	lifeTime = 0;
	/* ���� */
	double newRes = 0;
	do
	{
		newRes = MainPopulation[0].checkSubgrad();
		//printPopulation();
		crossoverPopulation();
		//printPopulation();
		mutationPopulation();
		eliminationPopulation();
		lifeTime++;
	} while (newRes > 0.1);
	printOptimum();
	allocations();
	generatePopulation();
	sortPopulation();
	lifeTime = 0;
	/* ���� */
	newRes = 0;
	do
	{
		newRes = MainPopulation[0].checkSubgrad();
		crossoverPopulation();
		mutationPopulation();
		eliminationPopulation();
		lifeTime++;
	} while (newRes > 0.01);
	printOptimum();
	allocations();
	generatePopulation();
	sortPopulation();
	lifeTime = 0;
	/* ���� */
	newRes = 0;
	do
	{
		newRes = MainPopulation[0].checkSubgrad();
		crossoverPopulation();
		mutationPopulation();
		eliminationPopulation();
		lifeTime++;
	} while (newRes > 0.001);
	printOptimum();
	allocations();
	generatePopulation();
	sortPopulation();
	lifeTime = 0;
	/* ���� */
	newRes = 0;
	do
	{
		newRes = MainPopulation[0].checkSubgrad();
		crossoverPopulation();
		mutationPopulation();
		eliminationPopulation();
		lifeTime++;
	} while (newRes > 0.0001);
	printOptimum();
}
