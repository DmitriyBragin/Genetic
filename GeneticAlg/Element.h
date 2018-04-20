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
	/* ��������� ������ */
	void allocateData();

	/* ����������� �������� */
	void setData(double *num);
	void setRoulettePercent(double num);
	void setSize(int num);

	/* ��������� ��������� ����� */
	double *getData() { return Data; }
	double getRoulettePercent() { return roulettePercent; }
	int getSize() { return size;  }

	/* ��������������� ������� �� ��������� */
	double fitnessFunction();
	double checkSubgrad();
	void printElement();
	void swapElements(Element b);

	Element operator/ (double num);
	Element operator+ (Element b);


};

#endif