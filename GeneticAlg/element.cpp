#include "Element.h"
#include <iostream>

double Element::fitnessFunction()
{
	return Data[0] * Data[0] + Data[1] * Data[1] + Data[0] + Data[1] + sqrt(1 + Data[0] * Data[0]);

	//return -2.0 * Data[0] * Data[0] - 3.0 * Data[1] * Data[1] + Data[0] + Data[1] + Data[0] * Data[0] * Data[0] + Data[1] * Data[1] * Data[1];

}
void Element::allocateData()
{
	Data = new double[size];
}

void Element::setData(double* num)
{
	for (int i = 0; i < size; i++)
	{
		Data[i] = num[i];
	}
}

void Element::setRoulettePercent(double num)
{
	roulettePercent = num;
}

void Element::setSize(int num)
{
	size = num;
}

Element Element::operator+(Element b)
{
	Element result;
	result.setSize(b.getSize());
	result.allocateData();
	double *temp = new double[size];
	double *bData = b.getData();
	for (int i = 0; i < size; i++)
	{
		temp[i] = Data[i] + bData[i];
	}
	result.setData(temp);
	return result;
}

Element Element::operator/(double num)
{
	Element result;
	result.setSize(size);
	result.allocateData();
	double *temp = new double[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = Data[i] / num;
	}
	result.setData(temp);
	return result;
}

void Element::printElement()
{
	std::cout << "(";
	for (int j = 0; j < size; j++)
	{
		std::cout << Data[j] << "; ";
	}
	std::cout << "); Percent: " << roulettePercent * 100.0 << " Fitness value: " << fitnessFunction() << std::endl;

}

void Element::swapElements(Element b)
{
	Element temp;
	temp.setSize(size);
	temp.setRoulettePercent(roulettePercent);
	temp.allocateData();
	double *bData = b.getData();
	double *tempData = temp.getData();
	for (int i = 0; i < size; i++)
	{
		tempData[i] = Data[i];
		Data[i] = bData[i];
		bData[i] = tempData[i];
	}
	b.setData(bData);
	delete tempData;
}

double Element::checkSubgrad()
{
	double resX = 0, resY = 0, res = 0;
	resX = Data[0] * (2.0 + 1.0 / (sqrt(1.0 + Data[0] * Data[0]))) + 1.0;
	resY = 2.0 * Data[1] + 1.0;

	res = sqrt(resX * resX + resY * resY);
	//std::cout << "SUBGRADIENT" << res << std::endl;
	return res;
}