#include <iostream>
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
		A[i] = new double[order];

	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			in >> A[i][j];
	
	TSLE matr(A,order);
	cout << matr.print() << endl <<endl;
	matr.switchRows(0, 1);
	cout << matr.print() << endl << endl;
	matr.switchCols(0, 1);
	cout << matr.print() << endl << endl;

	return 0;
}