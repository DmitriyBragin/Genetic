#include "Roulette.h"
#include <math.h>
#include <random>


void Roulette::prepareRoulette()
{
	double norm = 0, check = 0;;
	Element elem_0 = Pop.getElement(0);
	Element elem_sz = Pop.getElement(sizePopulation - 1);
	for (int i = 0; i < sizePopulation; i++)
	{
		Element elem_i = Pop.getElement(i);
		norm += elem_i.fitnessFunction() - elem_0.fitnessFunction();
	}
	//Pop.printPopulation();
	double fN_star = elem_sz.fitnessFunction() - elem_0.fitnessFunction();
	double N = sizePopulation;
	for (int i = 0; i < sizePopulation; i++)
	{
		double coeff = 2.0 * N * elem_0.fitnessFunction();
		double fN_N = fN_star * N;
		Element elem_i = Pop.getElement(i);
		double fi_star = elem_i.fitnessFunction() - elem_0.fitnessFunction();
		elem_i.setRoulettePercent((fN_star - fi_star) / (fN_N - norm));
		Pop.pushElement(elem_i, i);
		double newCheck = elem_i.getRoulettePercent();
		check += newCheck;
	}
	//Pop.printPopulation();
}

int Roulette::getArraySize()
{
	int size = 0;
	for (int i = 0; i < sizePopulation; i++)
	{
		Element elem = Pop.getElement(i);
		double percent = elem.getRoulettePercent();
		size += floor(percent * 1000.0);
	}
	return size;
}

double Roulette::spinRoulette()
{
	sizePopulation = Pop.getSizePopulation();
	prepareRoulette();
	//Pop.printPopulation();
	int *greatArray;
	int size = 0, index = 0, curpos = 0;
	size = getArraySize();
	if (size < 100)
	{
		Pop.printPopulation();
		return 0.0;
	}
	greatArray = new int[size];
	for (int i = 0; i < sizePopulation; i++)
	{
		Element elem = Pop.getElement(i);
		double percent = elem.getRoulettePercent();
		for (int j = 0; j < floor(percent * 1000.0); j++)
		{
			greatArray[curpos] = i;
			curpos++;
		}
	}
	std::random_shuffle(greatArray, greatArray + size);

	index = rand() % size;

	index = greatArray[index];
	delete greatArray;
	prepareRoulette();
	return index;
}