#pragma once
#ifndef POPULATION_H
#define POPULATION_H

#include "Element.h"
class Population
{
protected:
	Element * MainPopulation;
private:
	double sizePopulation;
	double sizeExpandedPopulation;
	double mutationCoeff;
	double probabilityCrossinogver;
	int spaceSize;
	int lifeTime;
public:
	Population(int sz, double mc, double pc, int ss) : sizePopulation(sz), mutationCoeff(mc), probabilityCrossinogver(pc),
	spaceSize(ss) {}
	void allocations();
	void printPopulation();
	void sortPopulation();
	void generatePopulation();
	void crossoverPopulation();
	int mutationPopulation();
	void eliminationPopulation();
	int *selection();
	void life();
	void printFitness();
	void printExpandedPopulation();
	void printOptimum();

	/* Получение приватных полей класса */
	Element getElement(int index);
	int getSizePopulation() { return sizePopulation; }
	int getSizeExpandedPopulation() { return sizeExpandedPopulation; }
	int getspaceSize() { return spaceSize; }

	/* Заполнение приватных полей класса */
	void pushElement(Element a, int index);

};
#endif
