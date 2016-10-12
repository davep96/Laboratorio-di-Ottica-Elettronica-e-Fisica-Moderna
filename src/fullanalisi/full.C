#include<iostream>
#include<fstream>
#include<cmath>
#include "lib.h"
measure dropanalysis(ifstream &, int);
void quick(measure*,int,int,int);

int main(){
	bool compat=true;
	int a;
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
		charges[count]=dropanalysis(inFile, count+1);

		count++;
		inFile>>a;

	}

	quick(charges,count,0,count-1);
	cout<<"n"<<"\t"<<"Charge value"<<"\t"<<"Charge error"<<"\t"<<"Relative error"<<endl;
	for (int i = 0; i < count; i++){
		cout<<charges[i].number<<"\t"<<charges[i].value<<"\t"<<charges[i].error<<"\t"<<100*charges[i].error/charges[i].value<<endl;
	}
	
	int numofclasses=0;
	
	for(int i=0; i<count;){
		numofclasses++;
		charges[i].classnum=numofclasses;
		int j=i+1;
		
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
	cout<<endl<<endl;

	cout<<"n"<<"\t"<<"Charge value"<<"\t"<<"Charge error"<<"\t"<<"Relative error"<<"\t"<<"Class"<<endl;
	for (int i = 0; i < count; i++){
		cout<<charges[i].number<<"\t"<<charges[i].value<<"\t"<<charges[i].error<<"\t"<<100*charges[i].error/charges[i].value<<"\t"<<charges[i].classnum<<endl;
	}
	return 0;
}