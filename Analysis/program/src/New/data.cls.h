#include <vector>
#include <stdlib.h>
#include <fstream>

class data{
	public:
	data(){};
	data(std::ifstream& inFile);
	~data(){};
	
	void plot();
	
	private:
	std::vector<measure> dataPoint;
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
