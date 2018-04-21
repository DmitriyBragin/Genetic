#pragma once
#ifndef ELIMINATION_H
#define ELIMINATION_H
#include "Population.h"
class Elimination
{
private:
	int sizePopulation;
	int spaceSize;
	int sizeExpandedPopulation;
	Population Pop;
public:
	Elimination(Population _p) : Pop(_p){
		sizePopulation = Pop.getSizePopulation();
		spaceSize = Pop.getspaceSize();
		sizeExpandedPopulation = Pop.getSizeExpandedPopulation();
	}

	void eliteElimination();
	void truncateElimination();
	void exclusionElimination();
};


#endif // !ELIMINATION_H
