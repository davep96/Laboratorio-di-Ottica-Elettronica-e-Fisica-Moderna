#include <iostream>
#include <fstream>
#include <cmath>
#include "lib.h"

using namespace std;

void parab(ifstream & inFile, int num){
	ofstream out;
	double x=0,x2=0,x3=0,x4=0,y=0,xy=0,x2y=0, expx,expy,delta,deltaA,deltaB,deltaC;
	for(int i=0; i<num; i++)
	{
		inFile>>expx;
		inFile>>expy;
		x=(double(i))/(double(i+1))*x+1/(double(i+1))*expx;
		x2=(double(i))/(double(i+1))*x2+1/(double(i+1))*pow(expx,2);
		x3=(double(i))/(double(i+1))*x3+1/(double(i+1))*pow(expx,3);
		x4=(double(i))/(double(i+1))*x4+1/(double(i+1))*pow(expx,4);
		y=(double(i))/(double(i+1))*y+1/(double(i+1))*expy;
		xy=(double(i))/(double(i+1))*xy+1/(double(i+1))*expx*expy;
		x2y=(double(i))/(double(i+1))*x2y+1/(double(i+1))*expx*expx*expy;
	}
	delta=num*(x2*x4-x3*x3)-x*(x*x4-x3*x2)+x2*(x*x3-x2*x2);
	deltaA=y*(x2*x4-x3*x3)-x*(xy*x4-x3*x2y)+x2*(xy*x3-x2*x2y);
	deltaB=num*(xy*x4-x3*x2y)-y*(x*x4-x3*x2)+x2*(x*x2y-x2*xy);
	deltaC=num*(x2*x2y-xy*x3)-x*(x*x2y-xy*x2)+y*(x*x3-x2*x2);
	out.open("parab.txt");
	out<<"y=A+Bx+Cx^2"<<endl;
	out<<"A \t B \t C"<<endl;
	out<<deltaA/delta<<"\t"<<deltaB/delta<<"\t"<<deltaC/delta<<endl;
	out.close();
	return;
}