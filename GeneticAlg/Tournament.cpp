#include "Tournament.h"
#include "Element.h"
#include <iostream>

void Tournament::prepareTournament()
{
	Pop.shufflePopulation();
    int i = 0, j = 0;
	Element firstCompetitor, secondCompetitor;
	while (i < sizePopulation - 1)
	{
		if (Pop.getElement(i).getTournamentStatus() == true)
		{
			firstCompetitor = Pop.getElement(i);
			j = i;
			while (Pop.getElement(i + 1).getTournamentStatus() == false)
				i++;
			secondCompetitor = Pop.getElement(i + 1);
			if (firstCompetitor.fitnessFunction() < secondCompetitor.fitnessFunction())
			{
				secondCompetitor.setTournamentStatus(false);
				Pop.pushElement(secondCompetitor, i + 1);
			}
			else
			{
				firstCompetitor.setTournamentStatus(false);
				Pop.pushElement(firstCompetitor, j);
			}
			i++;
		}
		i++;
	}
}

void Tournament::enableNewTournament()
{
	for (int i = 0; i < sizePopulation; i++)
	{
		Element temp = Pop.getElement(i);
		temp.setTournamentStatus(true);
		Pop.pushElement(temp, i);
	}
}

int* Tournament::determineWinner()
{
	/* Бинарный турнир */
	sizePopulation = Pop.getSizePopulation();
	if (Pop.getTournamentStatus() == true)
	{
		enableNewTournament();
		prepareTournament();
	}
	int winner1 = rand() % sizePopulation;
	int winner2 = rand() % sizePopulation;
	while(Pop.getElement(winner1).getTournamentStatus() == false)
		winner1 = rand() % sizePopulation;
	while ((Pop.getElement(winner2).getTournamentStatus() == false)||(winner2 == winner1))
		winner2 = rand() % sizePopulation;
	int *temp = new int[2];
	temp[0] = winner1;
	temp[1] = winner2;
	return temp;
}