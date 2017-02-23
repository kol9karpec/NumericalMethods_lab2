#pragma once

#include <iostream>
#include <cstring>

using namespace std;

#define DEFAULT_SIZE 5

class TSLE
{
private:
	double ** A;
	int order;
	//int * b;
public:
	TSLE();
	TSLE(TSLE&);
	TSLE(double ** A, int order);

	int * gauss(double * b);
	void switchRows(int row1, int row2);
	void switchCols(int col1, int col2);

	static bool searchNotZero(double ** A,int order, int & notZeroI, int & notZeroJ);

	char * print();
	~TSLE();
};



