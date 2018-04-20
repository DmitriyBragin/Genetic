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

	/* Дискретная рекомбинация (GAfinal, 18 страница */
	Element linearRecombination();
	Element intermediateRecombination();


	Element recombination();
};
#endif