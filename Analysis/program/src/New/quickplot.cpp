#include<iostream>
#include "cls.h"

int main(int argc, char* argv[]){
	if(argc<2)
	{
		std::cerr<<"Usage: "<<argv[0]<<" <input file name> "<<std::endl;
		return 1;
	}
	
	std::ifstream inFile;
	inFile.open(argv[1]);
	
	if(!inFile.good())
	{
		std::cerr<<"Error: no good file"<<std::endl;
		return 2;
	}
	
	data dataset(inFile);
	inFile.close();
	dataset.plot();
	return 0;
}