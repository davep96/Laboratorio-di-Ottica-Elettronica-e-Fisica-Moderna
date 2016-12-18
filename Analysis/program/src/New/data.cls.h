#include <vector>
#include <stdlib.h>
#include <fstream>
#include <math.h>

class data{
	public:
	data(){
		size=0;
		sum=0;
	};
	
	data(std::ifstream& inFile);
	~data(){};
	
	void plot();
	void sumcalc();
	double average();
	measure waverage();
	void add(measure m);
	
	private:
	std::vector<measure> dataPoint;
	int size;
	double sum;
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

void
data::sumcalc()
{
	double sumc=0;
	for(auto it: dataPoint)
	{
		sumc = sumc + it.value;
	}
	sum = sumc;
}

double
data::average()
{
	return sum/dataPoint.size();
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

void
data::add(measure m)
{
	dataPoint.push_back(m);
	
}
