#include <iostream>
#include <iomanip>
#include <fstream>
#include "TSLE.h"

using namespace std;

int main(int argc, const char* argv[])
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	double ** A;
	int order;
	/*cout << "Input order: ";*/ in >> order;
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
	
	TSLE matr(A,order);
	cout << matr.print() << endl <<endl;
	
	double ** x = matr.gauss(b, countB);
	cout << setprecision(3);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < countB; j++)
			cout << x[i][j] << "\t";
		cout << endl;
	}


	

	return 0;
}