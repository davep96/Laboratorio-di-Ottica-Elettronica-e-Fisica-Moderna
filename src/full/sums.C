#include <iostream>
#include <cmath>
#include "lib.h"
measure sums(measure* charge,int num,double seed, double error, bool forward, double errormin){

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
		
			if(sum1>sum2)
			
			{
				sumtot.value=seed+error;
				sumtot=sums(charge,num,sumtot.value,error,true,errormin);
			} 
			else 
			
			{
				sumtot.error=sumtot.error*99/100;
				sumtot=sums(charge,num, seed,sumtot.error,false,errormin);
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
		
			if(sum1>sum2)
			
			{
				sumtot.value=seed-error;
				sumtot=sums(charge,num,sumtot.value,sumtot.error,false,errormin);
			} 
			else 
			
			{
				sumtot.error=error*99/100;
				sumtot=sums(charge,num, seed,sumtot.error,true,errormin);
			}
		}
	}
	return sumtot;
	
}