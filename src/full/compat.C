#include <iostream>
#include <fstream>
#include <cmath>
#include "lib.h"

using namespace std;

void compat(double* values, double * errors, int number){
	int n=0.5*(number*number-number);
	double* z=new double[n];
	for(int i=0;i<number-1;i++){
		for(int j=i+1; j<number; j++){
			z[i+j-1]=(values[i]-values[j])/pow(pow(errors[i],-2)+pow(errors[j],-2),-0.5);
	}
}
	
	cout<<"z"<<"\t";
	for(int i=0; i<number; i++) cout<<"["<<i+1<<"]\t";
	cout<<endl;
	for(int i=0; i<number; i++){
		cout<<"["<<i+1<<"]\t";
		for(int j=0; j<number; j++){
			if(j<i){
				cout<<"\t";
			} else if(j==i){
				cout<<"x\t";
			} else{
				cout<<z[i+j-1]<<"\t";
			}
		}
		cout<<endl;
	}
}