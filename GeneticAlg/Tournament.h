#pragma once
#ifndef TOURNAMENT_H
#define TOURNAMENT_H
#include "Population.h"
class Tournament
{
private:
	double sizeExpandedPopulation;
	int sizePopulation;
	Population Pop;
public:
	Tournament(Population p) : Pop(p) {}
	void prepareTournament();
	int* determineWinner();
	void enableNewTournament();
};
#endif
