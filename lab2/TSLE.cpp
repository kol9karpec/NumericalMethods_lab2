#include "TSLE.h"



TSLE::TSLE()
{
	order = DEFAULT_SIZE;
	A = new int*[order];
	for (int i = 0; i < order; i++)
	{
		A[i] = new int[order];
		for (int j = 0; j < order; j++)
			A[i][j] = 0;
	}
	/*b = new int[order];
	for (int i = 0; i < order; i++)
		b[i] = 0;*/
}

TSLE::TSLE(TSLE & sle)
{
	order = sle.order;
	A = new int*[order];
	for (int i = 0; i < order; i++)
	{
		A[i] = new int[order];
		for (int j = 0; j < order; j++)
			A[i][j] = sle.A[i][j];
	}
	/*b = new int[order];
	for (int i = 0; i < order; i++)
		b[i] = sle.b[i];*/
}

TSLE::TSLE(const int ** A, const int order, const int * b)
{
	this->order = order;
	this->A = new int*[this->order];
	for (int i = 0; i < this->order; i++)
	{
		this->A[i] = new int[this->order];
		for (int j = 0; j < this->order; j++)
			this->A[i][j] = A[i][j];
	}
	/*this->b = new int[this->order];
	for (int i = 0; i < this->order; i++)
		this->b[i] = b[i];*/
}


TSLE::~TSLE()
{
	for (int i = 0; i < order; i++)
	{
		delete(A[i]);
		A[i] = nullptr;
	}
	delete(A);
	A = nullptr;
	/*delete(b);
	b = nullptr;*/
}
