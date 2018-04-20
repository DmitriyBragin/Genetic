#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H
class Element
{
private:
	double *Data;
	double roulettePercent;
	bool inTournament;
	int size;
public:
	/* ��������� ������ */
	void allocateData();

	/* ����������� �������� */
	void setData(double *num);
	void setRoulettePercent(double num);
	void setSize(int num);
	void setTournamentStatus(bool flag);

	/* ��������� ��������� ����� */
	double *getData() { return Data; }
	double getRoulettePercent() { return roulettePercent; }
	int getSize() { return size;  }
	bool getTournamentStatus() { return inTournament; }

	/* ��������������� ������� �� ��������� */
	double fitnessFunction();
	double checkSubgrad();
	void printElement();
	void swapElements(Element b);

	Element operator/ (double num);
	Element operator+ (Element b);
	Element operator- (Element b);
	Element operator* (double num);


};

#endif