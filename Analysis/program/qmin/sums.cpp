#include "lib.h"

int k(double Q, double q)
{
	return static_cast<int>(Q/q+0.5);
}

double sum(std::vector<double> vals, double q)
{
	double sumValue=0;
	for(auto i: vals)
	{
		sumValue+=pow((i/k(i,q)-q),2);
	}
	return sumValue;
}