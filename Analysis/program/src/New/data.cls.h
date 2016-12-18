#include <vector>
#include <stdlib.h>
#include <fstream>
#include <math.h>

class data{
	public:
	data(){};
	data(std::ifstream& inFile);
	~data(){};
	
	void plot();
	double sum();
	double average();
	measure waverage();
	
	private:
	std::vector<measure> dataPoint;
	int size;
};

data::data(std::ifstream& inFile)
{
	measure temp;
	double error, value;

	inFile>>error;
	inFile>>value;
	temp.add(value,error);
	while(inFile.good())
	{
		dataPoint.push_back(temp);
		inFile>>error;
		inFile>>value;
		temp.add(value,error);
	}
	dataPoint.push_back(temp);
	size=dataPoint.size();
}
void
data::plot()
{
	std::ofstream outFile("tempdata.txt");
	int n=0;
	for(auto i: dataPoint)
	{
		outFile<<++n<<"\t"<<i.value<<"\t"<<i.error<<std::endl;
	}
	outFile.close();
	std::system("gnuplot -p -e 'plot \"tempdata.txt\" with errorbars'");
	std::system("rm tempdata.txt");
}

double
data::sum()
{
	double sum=0;
	for(auto it: dataPoint)
	{
		sum = sum + it.value;
	}
	return sum;
}

double
data::average()
{
	return sum()/dataPoint.size();
}

measure
data::waverage()
{
	double pval=0, sump=0;
	for(auto it: dataPoint)
	{
		pval = pval + it.value/pow(it.error,2);
		sump = sump + pow(it.error,-2);
	}
	measure wave(pval/sump,pow(sump,-0.5));
	return wave;
}