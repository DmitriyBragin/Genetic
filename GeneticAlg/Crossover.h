#pragma once
#ifndef CROSSOVER_H
#define CROSSOVER_H
#include "Element.h"


class Crossover
{
private:
	Element Mother;
	Element Father;
public:
	Crossover(Element m, Element f) : Mother(m), Father(f) {}
	Crossover();
	Element recombination();
	void choosingParents();
	Element randomCrossover(); //TODO
};
#endif