#include <iostream>
#include <cmath>
#include "lib.h"
measure qerror(measure* charge,int num,double seed, double error, double target, bool forward, double errormin){

	measure sumtot;
	sumtot.value=seed;
	sumtot.error=error;
	
	while(sumtot.error>errormin){
		
		
		if(forward==true)
		{
		
			double sum1=0;
		
			for(int i=0; i<num; i++)

			{
				sum1+=pow((charge[i].value/(int (charge[i].value/seed+0.5))-seed),2);
			}
		
			double sum2=0;

			for(int i=0; i<num; i++)

			{
				sum2+=pow((charge[i].value/(int (charge[i].value/(seed+error)+0.5))-(seed+error)),2);
			}
			
			sum1=pow(pow(sum1-target,2),0.5);
			sum2=pow(pow(sum2-target,2),0.5);
			if(sum1>sum2)
			
			{
				sumtot.value=seed+error;
				sumtot=qerror(charge,num,sumtot.value,error,target,true,errormin);
			} 
			else 
			
			{
				sumtot.error=sumtot.error*99/100;
				sumtot=qerror(charge,num, seed,sumtot.error,target,false,errormin);
			}
		} 
		else 
		
		{
			double sum1=0;
		
			for(int i=0; i<num; i++)
			
			{
				sum1+=pow((charge[i].value/(int (charge[i].value/seed+0.5))-seed),2);
			}


			double sum2=0;
			
			for(int i=0; i<num; i++)
			
			{
				sum2+=pow((charge[i].value/(int (charge[i].value/(seed-error)+0.5))-(seed-error)),2);
			}
			
			sum1=pow(pow(sum1-target,2),0.5);
			sum2=pow(pow(sum2-target,2),0.5);
			if(sum1>sum2)
			
			{
				sumtot.value=seed-error;
				sumtot=qerror(charge,num,sumtot.value,sumtot.error,target,false,errormin);
			} 
			else 
			
			{
				sumtot.error=error*99/100;
				sumtot=qerror(charge,num, seed,sumtot.error,true,target,errormin);
			}
		}
	}
	return sumtot;
}