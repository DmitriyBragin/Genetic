#include "Population.h"
#include "Roulette.h"
#include "Element.h"
#include "Crossover.h"
#include "Tournament.h"
#include "Selection.h"
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

int* Population::selection()
{
	int *parent = new int[spaceSize];
	Selection S(*this);
	/* Селекция на основе рулетки с защитой от клонирования */
	//parent = S.rouletteSelection(); // Работает и на 40
	/* Турнирная селекция с защитой от клонирования */
	//parent = S.tournamentSelection(); // Со 100 сошелся
	/* Случайная селекция */
	//parent = S.panmixedSelection(); // Со 100 сошелся
	/* Инбридинг */
	//parent = S.inbreedSelection(); // Не работает на 100, сошелся на 1000
	/* Аутбридинг */
	parent = S.outbreedSelection();
	return parent;
}

void Population::crossoverPopulation()
{

int count = 0;

	int firstParent = 0, secondParent = 0;
	double koeff = 0.5;

	for (int i = sizePopulation; i < sizeExpandedPopulation; i++)
	{
		/* Выбор родителей */
		int* parents = selection();
		/* Рекомбинация */
		Element Mother = MainPopulation[parents[0]];
		Element Father = MainPopulation[parents[1]];
		Crossover C(Mother, Father);
		Element Child = C.recombination();
		MainPopulation[i].setData(Child.getData());
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
	for (int i = sizePopulation; i < sizeExpandedPopulation; i++)
	{
		double *coords = new double[spaceSize];
		for (int j = 0; j < spaceSize; j++)
		{
			coords[j] = NAN;
		}
		MainPopulation[i].setData(coords);
	}
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

	/* Первичное создание и генерация популяции */
	generatePopulation();
	sortPopulation();
	lifeTime = 0;
	/* Цикл */
	double newRes = 0;
	do
	{
		newRes = MainPopulation[0].checkSubgrad();
		crossoverPopulation();
		mutationPopulation();
		//printPopulation();
		sortPopulation();
		eliminationPopulation();
		lifeTime++;
	} while (newRes > 0.0001);
	printOptimum();
}
