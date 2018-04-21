#pragma once
#ifndef SELECTION_H
#define SELECTION_H
#include "Population.h"
#include "Roulette.h"
#include "Tournament.h"

class Selection
{
private:
	int sizePopulation;
	int sizeExpandedPopulation;
	int spaceSize;
	int* parent;
	Population Pop;
public:
	Selection(Population _p) : Pop(_p) {
		spaceSize = Pop.getspaceSize();
		sizePopulation = Pop.getSizePopulation();
		parent = new int[spaceSize];
	}
	int* tournamentSelection();
	int* rouletteSelection();
	int* panmixedSelection();
	int* inbreedSelection();
	int* outbreedSelection();
};





#endif // ! SELECTION_H

