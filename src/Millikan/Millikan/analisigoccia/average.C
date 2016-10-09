//Simple program that returns an average
#include<iostream>
#include<fstream>
#include<cmath>
#include "lib.h"

double average(double * values, int size){
	
	double sum=0,avg;
	
	for(int i=0;i<size;i++){
		sum=sum+values[i];
	}
	avg=sum/size;
	
	return avg;
}