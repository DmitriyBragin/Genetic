#pragma once
#ifndef POPULATION_H
#define POPULATION_H

#include "Element.h"
class Population
{
private:
	int sizePopulation;
	double sizeExpandedPopulation;
	double mutationCoeff;
	int spaceSize;
	int lifeTime;
	bool tournamentStatus;
	Element * MainPopulation;
public:
	Population(int sz, double mc, int ss) : sizePopulation(sz), mutationCoeff(mc),
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
	void shufflePopulation();
	void printExpandedPopulation();
	void printOptimum();
	void sortParents();
	void sortChilds();

	/* Получение приватных полей класса */
	Element getElement(int index);
	int getSizePopulation() { return sizePopulation; }
	int getSizeExpandedPopulation() { return sizeExpandedPopulation; }
	int getspaceSize() { return spaceSize; }
	bool getTournamentStatus() { return tournamentStatus; }
	/* Заполнение приватных полей класса */
	void pushElement(Element a, int index);
	void setTournamentStatus(bool flag) { tournamentStatus = flag; }

};
#endif
