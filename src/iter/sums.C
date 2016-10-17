#include <iostream>
#include <cmath>
#include "lib.h"
double sums(measure* charge,int num,double seed, double error, bool forward, double errormin){
	while(error>errormin){
		if(forward==true){
			double sum1=0;
			for(int i=0; i<num; i++){
				sum1+=pow((charge[i].value/(int (charge[i].value/seed+0.5))-seed),2);
			}
			
			double sum2=0;
			for(int i=0; i<num; i++){
				sum2+=pow((charge[i].value/(int (charge[i].value/(seed+error)+0.5))-(seed+error)),2);
			}
			double sumtot;
			if(sum1>sum2){
				sumtot=sums(charge,num,sum2,error,forward,errormin);
			} else {
				forward=false;
				sumtot=sums(charge,num, sum2,error/2,forward,errormin);
			}
		} else {
			double sum1=0;
			for(int i=0; i<num; i++){
				sum1+=pow((charge[i].value/(int (charge[i].value/seed+0.5))-seed),2);
			}
			
			double sum2=0;
			for(int i=0; i<num; i++){
				sum2+=pow((charge[i].value/(int (charge[i].value/(seed-error)+0.5))-(seed-error)),2);
			}
			double sumtot;
			if(sum1>sum2){
				sumtot=sums(charge,num,sum2,error,forward,errormin);
			} else {
				forward=true;
				sumtot=sums(charge,num, sum2,error/2,forward,errormin);
			}
		}
	}
	
}