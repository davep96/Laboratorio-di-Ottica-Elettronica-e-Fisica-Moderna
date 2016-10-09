#include<iostream>
#include<fstream>
#include<cmath>
#include "lib.h"
charge dropanalysis(ifstream &);
int main(){
	
	int a;
	int count=0;
	charge* charges=new charge[count];
	ifstream inFile;
	inFile.open("data.txt");
	
	inFile>>a;
	
	while(!(inFile.eof())){

		charge* temp=new charge[count+1];
		for(int i=0;i<count;i++){
			temp[i].value=charges[i].value;
			temp[i].error=charges[i].error;
		}
		delete charges;
		charges = temp;
		charges[count]=dropanalysis(inFile);
		count++;
		inFile>>a;

	}
	cout<<"n"<<"\t"<<"Charge value"<<"\t"<<"Charge error"<<"\t"<<"Relative error"<<endl;
	for (int i = 0; i < count; i++){
		cout<<i+1<<"\t"<<charges[i].value<<"\t"<<charges[i].error<<"\t"<<100*charges[i].error/charges[i].value<<endl;
	}
	
	
	
	return 0;
}