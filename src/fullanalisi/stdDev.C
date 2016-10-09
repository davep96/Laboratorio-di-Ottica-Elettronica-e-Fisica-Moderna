//Returns the sample standard deviation
#include<iostream>
#include<fstream>
#include<cmath>
#include"lib.h"

double stdDevS(double*values,int size){

	double sum=0,avg,stdDev;
	
	for(int i=0;i<size;i++){
		sum=sum+values[i];
	}
	avg=sum/size;
	sum=0;
	for(int i=0;i<size;i++){
		sum=sum+(values[i]-avg)*(values[i]-avg);
	}
	stdDev=sqrt(sum/(size-1));
	return stdDev;
}