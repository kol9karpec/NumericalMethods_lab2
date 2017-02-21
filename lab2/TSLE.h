#pragma once

#define DEFAULT_SIZE 5

class TSLE
{
private:
	int ** A;
	int order;
	//int * b;
public:
	TSLE();
	TSLE(TSLE&);
	TSLE(const int ** A, const int order, const int * b);

	int * gauss(const int * b);
	~TSLE();
};

