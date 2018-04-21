#include "Elimination.h"
#define NAN 100

void Elimination::eliteElimination()
{
	Pop.sortPopulation();
	for (int i = sizePopulation; i < sizeExpandedPopulation; i++)
	{
		double *coords = new double[spaceSize];
		for (int j = 0; j < spaceSize; j++)
		{
			coords[j] = NAN;
		}
		Pop.getElement(i).setData(coords);
	}
}

void Elimination::truncateElimination()
{
	Pop.sortParents();
	Pop.sortChilds();
	int k = 0;
	for (int i = sizePopulation; i < 1.25 * sizePopulation; i++)
	{
		Pop.pushElement(Pop.getElement(i), 0.75 * sizePopulation + k);
		k++;
	}
}

void Elimination::exclusionElimination()
{
	Pop.sortParents();
	Pop.sortChilds();
	bool flag = false;
	int iterator = 1;
	for (int i = sizePopulation; i < sizeExpandedPopulation; i++)
	{
		flag = true;
		for (int j = 0; j < sizePopulation; j++)
		{
			if (Pop.getElement(i) == Pop.getElement(j))
			{
				Pop.getElement(i).deleteElement();
				flag = false;
				break;
			}
		}
		if (flag == true)
		{
			Pop.pushElement(Pop.getElement(i), sizePopulation - iterator);
			iterator++;
		}
	}
}