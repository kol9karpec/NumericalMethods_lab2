#include <iostream>
#include <iomanip>
#include <fstream>
#include "TSLE.h"

#define EPS 0.00001

using namespace std;

int main(int argc, const char* argv[])
{
	char * inFile = new char[20];
	char * outFile = new char[20];
	if (argc > 1) strcpy(inFile, argv[1]);
	else strcpy(inFile, "input.txt");
	if (argc > 2) strcpy(outFile, argv[2]);
	else strcpy(outFile, "output.txt");

	ifstream in(inFile);
	ofstream out(outFile);
	
	int order;
	in >> order;

	double ** A;
	A = new double*[order];

	for (int i = 0; i < order; i++)
	{
		A[i] = new double[order];
		for (int j = 0; j < order; j++)
			in >> A[i][j];
	}

	int countB;
	in >> countB;

	double ** b = new double*[order];
	for (int i = 0; i < order; i++)
		b[i] = new double[countB];

	for (int j = 0; j < countB; j++)
		for (int i = 0; i < order; i++)
			in >> b[i][j];

	double ** diagM = new double*[order];
	for (int i = 0; i < order; i++)
	{
		diagM[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			if (i == j) diagM[i][j] = 1;
			else diagM[i][j] = 0;
		}
	}
		

	
	TSLE matr(A,order);
	
	double det = 0;
	double ** x = matr.gauss(b, countB, det);
	double buf = 0;
	double ** reverseMatr = matr.gauss(diagM, order, buf);

	if (x == NULL) out << "Degenerate system!" << endl;
	else
	{
		double ** residuals = matr.residualsVect(b, countB);
		out << setprecision(-(int)(log10(EPS/10)));
		out << "Roots: " << endl;
		for (int i = 0; i < order; i++)
		{
			for (int j = 0; j < countB; j++)
				out << x[i][j] << "\t";
			out << endl;
		}
		out << "Residuals: " << endl;
		for (int i = 0; i < order; i++)
		{
			for (int j = 0; j < countB; j++)
				out << residuals[i][j] << "\t";
			out << endl;
		}
		out << "Determinant: " << det << endl;
		out << "Reverse matrix: " << endl;
		for (int i = 0; i < order; i++)
		{
			for (int j = 0; j < order; j++)
				out << reverseMatr[i][j] << "\t";
			out << endl;
		}
	}

	delete[] inFile;
	delete[] outFile;

	for (int i = 0; i < order; i++)
		delete[] A[i];
	delete[] A;

	for (int i = 0; i < order; i++)
		delete[] b[i];
	delete[] b;

	for (int i = 0; i < order; i++)
		delete[] x[i];
	delete[] x;

	for (int i = 0; i < order; i++)
		delete[] reverseMatr[i];
	delete[] reverseMatr;

	in.close();
	out.close();

	return 0;
}