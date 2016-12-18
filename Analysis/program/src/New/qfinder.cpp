#include<iostream>
#include "cls.h"


int main (int argc, char* argv[])
{
	if(argc<2)
	{
		std::cerr<<"Usage: "<<argv[0]<<" <file name>> "<<std::endl;
		return 1;
	}
	std::inFile(argv[1]);
	if(!inFile.good())
	{
		std::cerr<<"Error: bad file"<<std::endl;
		return 2;
	}
	
	data qvals;
	std::ofstream outFile("tempData.txt");
	double a;
	inFile>>a;
	while(inFile.good())
	{
		outFile<<a<<"\t"<<0<<std::endl;
		inFile>>a;
	}
	outFile<<a<<"\t"<<0<<std::endl;
	
	outFile.close();
	inFile.close();
	
	inFile.open("tempData.txt");
	
	qvals(inFile);
	inFile.close();
	std::system("rm tempData.txt");
	
	
	return 0;
}