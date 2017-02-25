#include "TSLE.h"



TSLE::TSLE()
{
	order = DEFAULT_SIZE;
	A = new double*[order];
	for (int i = 0; i < order; i++)
	{
		A[i] = new double[order];
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
	A = new double*[order];
	for (int i = 0; i < order; i++)
	{
		A[i] = new double[order];
		for (int j = 0; j < order; j++)
			A[i][j] = sle.A[i][j];
	}
	/*b = new int[order];
	for (int i = 0; i < order; i++)
		b[i] = sle.b[i];*/
}

TSLE::TSLE(double ** A, int order)
{
	this->order = order;
	this->A = new double*[this->order];
	for (int i = 0; i < this->order; i++)
	{
		this->A[i] = new double[this->order];
		for (int j = 0; j < this->order; j++)
			this->A[i][j] = A[i][j];
	}
	/*this->b = new int[this->order];
	for (int i = 0; i < this->order; i++)
		this->b[i] = b[i];*/
}


double ** TSLE::gauss(double ** b, int count)
{
	TSLE copyA(*this);
	copyA.print();

	double ** x = new double*[order];
	for (int i = 0; i < order; i++)
	{
		x[i] = new double[count];
		for(int j=0;j<count;j++)
			x[i][j] = 0;
	}
		

	int curI=0, curJ=0;
	int notZeroI;
	while (curI < this->order)
	{
		if (searchNotZero(copyA.A, order,curI, curJ, notZeroI))
		{
			//making not zero elem row top 
			switchRows(notZeroI, curI);
			//doing Gauss
			for (int i = 0; i < order; i++)
			{
				if (i != curI)
				{
					//making current elem zero
					double k = copyA.A[i][curJ]/copyA.A[curI][curJ];
					//cout << "k = " << copyA.A[i][curJ] << "/" << copyA.A[curI][curJ] << endl;
					for (int j = 0; j < order; j++)
					{
						if (j == curJ) copyA.A[i][j] = 0;
						else copyA.A[i][j] -= k*copyA.A[curI][j];
						//cout << copyA.print() << endl << endl;
					}
					for (int j = 0; j < count; j++)
						b[i][j] -= b[curI][j] * k;	
				}				
			}		
			curI++; curJ++;
		}
		else
		{
			return NULL;
		}
	}		

	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < count; j++)
		{
			x[i][j] = b[i][j] / copyA.A[i][i];
		}
	}

	//copyA.~TSLE();

	return x;
}

void TSLE::switchRows(int row1, int row2)
{
	if ((row1 > this->order - 1) | (row2 > this->order - 1))
		cout << "Row number overlimit!" << endl;
	else
	{
		double * buf = A[row1];
		A[row1] = A[row2];
		A[row2] = buf;
	}
}

void TSLE::switchCols(int col1, int col2)
{
	if ((col1 > this->order - 1) | (col2 > this->order - 1))
		cout << "Row number overlimit!" << endl;
	else
	{
		for (int i = 0; i < this->order; i++)
		{
			double buf = A[i][col1];
			A[i][col1] = A[i][col2];
			A[i][col2] = buf;
		}		
	}
}

bool TSLE::searchNotZero(double ** A, int order, int iFrom, int jFrom, int & notZeroI)
{
	notZeroI = 0;
	for (int i = iFrom; i < order; i++)
		if (A[i][jFrom] != 0)
		{
			notZeroI = i;
			return true;
		}
	return false;
}

char * TSLE::print()
{
	int size = (this->order * 6)*this->order;
	char * result = new char[size];
	strcpy(result, "");
	for (int i = 0; i < this->order; i++)
	{
		for (int j = 0; j < this->order; j++)
		{
			char * buff = new char[256];
			sprintf(buff, "%2.2f", A[i][j]);
			strcat(result,buff);
			delete(buff);
			if(j < this->order-1) strcat(result,"\t");
		}
		if (i < this->order - 1) strcat(result,"\n");
	}

	return result;
}

TSLE::~TSLE()
{
	for (int i = 0; i < order; i++)
	{
		delete[](A[i]);
		A[i] = nullptr;
	}
	delete[](A);
	A = nullptr;
	/*delete(b);
	b = nullptr;*/
}
