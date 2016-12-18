#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>

class plotgraph{
	public:
	plotgraph(std::ifstream inFile)
	{
		double x, y;
		inFile>>x>>y;
		while(inFile.good())
		{
			plotpoint newpoint(x,y);
			points.push_back(newpoint);
			inFile>>x>>y;
		}
		
		plotpoint newpoint(x,y);
		points.push_back(newpoint);
		size=points.size();
	}
	
	plotgraph(){
		size=0;
	}
	
	~plotgraph(){};
	
	void add(plotpoint p)
	{
			
	}
	
	private:
	std::vector<plotpoint> points;
	int size;
}