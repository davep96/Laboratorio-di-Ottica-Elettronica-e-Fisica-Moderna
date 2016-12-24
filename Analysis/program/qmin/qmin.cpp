#include "lib.h"
const double ratio=0.9;

double min(std::vector<double> vals, double seed, double error, double errormin,std::ofstream& out)
{
	if(error>errormin||error<-errormin)
	{
		double sum1=0, sum2=0;
		sum1=sum(vals,seed);
		sum2=sum(vals,seed+error);
		out<<seed+error<<"\t"<<sum2<<std::endl;
		if(sum1>sum2)
		{
			seed=min(vals,seed+error,error,errormin,out);
		} else
		{
			seed=min(vals,seed,-error*ratio,errormin,out);
		}
	}
	return seed;
}