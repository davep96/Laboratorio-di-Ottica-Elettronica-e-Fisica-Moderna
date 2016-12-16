#include <iostream>
#include <cmath>
#include <fstream>
#include "lib.h"
measure sums(measure* charge,int num,double seed, double error, bool forward, double errormin, ofstream & outFile){

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
			outFile<<seed+error<<"\t"<<sum2<<endl;
			if(sum1>sum2)
			
			{
				sumtot.value=seed+error;
				sumtot=sums(charge,num,sumtot.value,error,true,errormin,outFile);
			} 
			else 
			
			{
				sumtot.error=sumtot.error*0.99;
				sumtot=sums(charge,num, seed,sumtot.error,false,errormin,outFile);
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
			outFile<<seed-error<<"\t"<<sum2<<endl;
			if(sum1>sum2)
			
			{
				sumtot.value=seed-error;
				sumtot=sums(charge,num,sumtot.value,sumtot.error,false,errormin,outFile);
			} 
			else 
			
			{
				sumtot.error=error*0.99;
				sumtot=sums(charge,num, seed,sumtot.error,true,errormin,outFile);
			}
		}
	}
	return sumtot;
	
}