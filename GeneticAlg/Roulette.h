#pragma once
#ifndef ROULETTE_H
#define ROULETTE_H
#include "Population.h"
class Roulette
{
private:
	double sizeExpandedPopulation;
	int sizePopulation;
	Population Pop;
public:
	Roulette(Population p) : Pop(p) {}
	double spinRoulette();
	void prepareRoulette();
};
#endif