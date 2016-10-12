#include<iostream>
#include<fstream>
#include<cmath>
#include "lib.h"

void quick(measure*,int,int,int);
int falsefact(int n);

int main(){
	bool compat=true;
	double a;
	int count=0;
	measure* charges=new measure[count];
	ifstream inFile;
	inFile.open("data.txt");
	
	inFile>>a;
	while(!(inFile.eof())){
		measure* temp=new measure[count+1];
		for(int i=0;i<count;i++){
			temp[i].number=charges[i].number;
			temp[i].value=charges[i].value;
			temp[i].error=charges[i].error;
		}
		delete charges;
		charges = temp;
		charges[count].value=a;
		charges[count].number=count+1;
		charges[count].error=5*charges[count].value/100;
		count++;
		inFile>>a;
	}

	quick(charges,count,0,count-1);

	
	
	//Division in classes
	int numofclasses=0;
	
	for(int i=0; i<count;){
		numofclasses++;
		charges[i].classnum=numofclasses;

		int j=i+1;
		compat=true;
		while(compat==true){
			if(j==count){
				compat=false;
				continue;
			}
			double z=0;
			z=charges[i].value-charges[j].value;
			z=z/sqrt(pow(charges[i].error,2)+pow(charges[j].error,2));
			z=sqrt(pow(z,2));
			if(z>2){
				compat=false;
			} else {
				charges[j].classnum=numofclasses;
				j++;
			}	
		}
		i=j;
	}
	ofstream outFile;
	outFile.open("output.txt");
	outFile<<"n"<<"\t"<<"Charge value"<<"\t"<<"Charge error"<<"\t"<<"Relative error"<<"\t"<<"Class"<<endl;
	for (int i = 0; i < count; i++){
		outFile<<charges[i].number<<"\t"<<charges[i].value<<"\t"<<charges[i].error<<"\t"<<100*charges[i].error/charges[i].value<<"\t"<<charges[i].classnum<<endl;
	}
	outFile.close();

	
	//Class formation
	measure* classes=new measure[numofclasses];
	int j=0;
	
	for(int i=0;i<numofclasses;i++){
		classes[i].value=0;
		classes[i].error=0;
		double denom=0;
		
		while(charges[j].classnum==i+1){
			classes[i].value=classes[i].value+charges[j].value/
							(pow(charges[j].error,2));
			denom=denom + 1/(pow(charges[j].error,2));
			
			classes[i].error=classes[i].error+pow(charges[j].error,-2);
			j++;
		}
		classes[i].value=classes[i].value/denom;
		classes[i].error=pow(classes[i].error, -0.5);
		
	}
	outFile.open("classes.txt");
	
	outFile<<"Class number \t Class Value \t Class error \t"<<endl;
	for(int i=0;i<numofclasses; i++){
		outFile<<i+1<<"\t"<<classes[i].value<<"\t"<<classes[i].error<<endl;
	}
	outFile.close();
	
	//Evaluation of differences
	int numdiff=0;
	measure *diff=new measure[falsefact(numofclasses-1)];
	for( int i = 0 ; i < numofclasses -1; i++){
		for(int k = i+1 ; k< numofclasses; k++){
			diff[numdiff].value=-classes[i].value+classes[k].value;
			diff[numdiff].error=pow(pow(classes[i].error,2)+pow(classes[k].error,2),0.5);
			numdiff++;
		}
	}

	
	return 0;
}