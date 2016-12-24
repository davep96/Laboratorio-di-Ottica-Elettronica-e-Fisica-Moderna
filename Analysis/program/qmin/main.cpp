#include "lib.h"

int main(int argc, char* argv[])
{
	/*
	if(argc<2)
	{
		std::cerr<<"Too few arguments"<<std::endl;
		return 1;
	}
	
	std::ifstream in(argv[1]);
	
	if(!in.good())
	{
		std::cerr<<"Bad file"<<std::endl;
		return 2;
	}
	*/
	std::ifstream in("data.txt");
	
	double a;
	std::vector<double> qvals;
	
	in>>a;
	
	while(in.good())
	{
		qvals.push_back(a*1e19);
		in>>a;
	}
	
	qvals.push_back(a*1e19);
	double qmin;
	std::ofstream out("parpnt.txt");
	qmin=min(qvals,1,1,1e-30,out);
	std::cout<<qmin<<std::endl;
	std::system("gnuplot -p -e \"plot \'parpnt.txt\'\"");
	
	std::cout<<sum(qvals,1)<<std::endl;
	std::cout<<sum(qvals,1.6)<<std::endl;
	std::cout<<sum(qvals,6.27129e-09)<<std::endl;
	return 0;
}