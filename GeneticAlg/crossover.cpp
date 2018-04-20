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
	Child = Mother + (Father - Mother) * d;

	return Child;
}

Element Crossover::recombination()
{
	Element Child;
	Child = linearRecombination();
	//Child = intermediateRecombination();
	return Child;
}