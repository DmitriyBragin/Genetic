#include "Crossover.h"
#include "Element.h"

Element Crossover::recombination()
{

	double koeff = 0.5;
	Element Child;
	Child.setSize(Mother.getSize());
	Child.setRoulettePercent(0.0);
	Child.allocateData();
	double *recombination = new double[Child.getSize()];
	Child = Mother + Father;
	Child = Child / 2;
	return Child;
}