#include "Crossover.h"
#include "Element.h"
#include <iostream>

Element Crossover::linearRecombination()
{
	Element Child;
	Child.setSize(Mother.getSize());
	Child.setRoulettePercent(0.0);
	Child.allocateData();
	double *recombination = new double[Child.getSize()];

	/* ������� ������������ ���� + ���� ������� */
	Child = (Mother + Father)/2;
	return Child;
}

Element Crossover::intermediateRecombination()
{
	Element Child;
	Child.setSize(Mother.getSize());
	Child.setRoulettePercent(0.0);
	Child.allocateData();
	double *recombination = new double[Child.getSize()];

	double d = (double)(rand()) / RAND_MAX * 1.5 - 0.25; // d ����������� [-0.25;1.25]
	//d = (double)(rand()) / RAND_MAX; // d ����������� [0;1]
	Child = Mother + (Father - Mother) * d;

	return Child;
}

Element Crossover::directionRecombination()
{
	Element Child;
	Child.setSize(Mother.getSize());
	Child.setRoulettePercent(0.0);
	Child.allocateData();
	double *recombination = new double[Child.getSize()];

	/* ������� ������������ ���� + ���� ������� */
	if (Mother.fitnessFunction() < Father.fitnessFunction())
		Child = Mother * 0.75 + Father * 0.25;
	else Child = Mother * 0.25 + Father * 0.75;
	return Child;
}

Element Crossover::recombination()
{
	Element Child;
	//Child = linearRecombination();
	//Child = intermediateRecombination();
	Child = directionRecombination();
	return Child;
}