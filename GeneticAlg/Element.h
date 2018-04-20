#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H
class Element
{
private:
	double *Data;
	double roulettePercent;
	int size;
public:
	/* Выделение памяти */
	void allocateData();

	/* Простановка значений */
	void setData(double *num);
	void setRoulettePercent(double num);
	void setSize(int num);

	/* Получение приватных полей */
	double *getData() { return Data; }
	double getRoulettePercent() { return roulettePercent; }
	int getSize() { return size;  }

	/* Вспомогательные функции от элементов */
	double fitnessFunction();
	double checkSubgrad();
	void printElement();
	void swapElements(Element b);

	Element operator/ (double num);
	Element operator+ (Element b);


};

#endif