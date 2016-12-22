#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>

int mult(double q, double e)
{
	int k;
	k= static_cast <int> (q/e + 0.5);
	return k;
}

double sumcalc(std::vector<double> *qvals, double e)
{
	double s=0;
	for(auto i: &qvals)
	{
		s = s + pow(i/mult(i,e)-e,2);
	}
	return s;
}

double qmin (std::vector<double> *qvals, bool forward, double seed, double error, double errormin, std::ofstream outFile)
	{
		double qminimum;
		while(errormin<error)
		{
			double sum1, sum2;
			if(forward == true)
			{
				sum1=sumcalc(qvals,seed);
				sum2=sumcalc(qvals,seed+error);
				outFile<<seed + error<<"\t"<<seed;
				if(sum2<sum1)
				{
					qminimum = qmin(qvals,true,seed+error,error,errormin,outFile)
				}
				else
				{
					error = error*0.99;
					qminimum = qmin(qvals,false, seed+error,error,errormin,outFile)
				}
			}
			else 
			{
				sum1=sumcalc(qvals,seed);
				sum2=sumcalc(qvals,seed-error);
				outFile<<seed-error<<"\t"<<seed;
				if(sum2<sum1)
				{
					qminimum
			}
		}
		
	}

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		std::cerr<<"Usage: "<<argv[0]<<" <filename> "<<std::endl;
		return 1;
	}

	std::ifstream inFile(argv[1]);
	
	if(!inFile.good())
	{
		std::cerr<<"Error: bad file"<<std::endl;
		return 2;		
	}
	
	std::vector<double> charges;
	
	double a;
	inFile>>a;
	while(inFile.good())
	{
		charges.push_back(a);
		inFile>>a;	
	}
	charges.push_back(a);

	
	return 0;
}
