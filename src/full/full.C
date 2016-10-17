#include<iostream>
#include<fstream>
#include<cmath>
#include "stdlib.h"
#include "lib.h"

measure dropanalysis(ifstream &, int);
void quick(measure*,int,int,int);
int falsefact(int n);
double wave(measure * a, int n);
double wdevstd(measure * a, int n);
measure sums(measure* charge,int num,double seed, double error, bool forward, double errormin);
measure qerror(measure* charge,int num,double seed, double error, double target, bool forward, double errormin);

int main(){
	bool compat=true;
	double a;
	measure q;
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
	ofstream outFile;
	outFile.open("expCharges.txt");
	quick(charges,count,0,count-1);
	outFile<<"n"<<"\t"<<"Charge value"<<"\t"<<"Charge error"<<"\t"<<"Relative error"<<endl;
	for (int i = 0; i < count; i++){
		outFile<<charges[i].number<<"\t"<<charges[i].value<<"\t"<<charges[i].error<<"\t"<<100*charges[i].error/charges[i].value<<endl;
	}
	outFile.close();
	
	
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
	//Add differences to charges
	measure* temp = new measure [count+numdiff];
	for(int i=0; i<count; i++){
		temp[i]=charges[i];
	}
	for(int i=0; i<numdiff; i++){
		temp[count+i]=diff[i];
	}
	free (charges);
	free (diff);
	charges = temp;
	
	quick(charges, count+numdiff, 0, count+numdiff-1);
	
	//Redivision in classes
	count= count+numdiff;
	numofclasses=0;
	
	for(int i=0; i<count;){
		numofclasses++;
		charges[i].classnum=numofclasses;

		int k=i+1;
		compat=true;
		while(compat==true){
			if(k==count){
				compat=false;
				continue;
			}
			double z=0;
			z=charges[i].value-charges[k].value;
			z=z/sqrt(pow(charges[i].error,2)+pow(charges[k].error,2));
			z=sqrt(pow(z,2));
			if(z>2){
				compat=false;
			} else {
				charges[k].classnum=numofclasses;
				k++;
			}	
		}
		i=k;
	}
	
	//Reformation of classes
	
	j=0;
	q.value=0;
	q.error=0;
	while(charges[j].classnum==1){
		q.value=q.value+charges[j].value;
		j++;
	}
	
	q.value=q.value/j;
	
	for(int i=0; i<count; i++){
		charges[i].classnum=charges[i].value/q.value+0.5;
	}
	
	for(int i=0; i<count; i++){
		charges[i].value=charges[i].value/(charges[i].classnum);
		charges[i].error=charges[i].error/(charges[i].classnum);
	}
	
	outFile.open("chargesComplete.txt");
	outFile<<"n \t Value \t Error \t k"<<endl;
	for(int i=0; i<count; i++){
		outFile<<i+1<<"\t"<<charges[i].value<<"\t"<<charges[i].error<<"\t"<<charges[i].classnum<<endl;
	}
	outFile.close();
	
	q.value = wave(charges,count);
	q.error = wdevstd(charges,count);
	outFile.open("result.txt");
	outFile<<"Metodo media pesata"<<endl;
	outFile<<"Value \t Error \t Relative error \t z"<<endl;
	outFile<<q.value<<"\t"<<q.error<<"\t"<<q.error/q.value<<"\t"<<pow(pow((q.value-1.604)/q.error,2),0.5)<<endl;
	q.value=0;
	q.error=0;
	for(int i=0; i<count; i++){
		q.value=q.value+charges[i].value;
	}
	q.value=q.value/count;
	for(int i=0; i<count ; i++){
		q.error=q.error+pow(q.value-charges[i].value,2);
	}
	q.error=q.error/((count-1)*count);
	q.error=sqrt(q.error);
	
	outFile<<"Metodo media non pesata, errore = dev std"<<endl;
	outFile<<"Value \t Error \t Relative error \t z"<<endl;
	outFile<<q.value<<"\t"<<q.error<<"\t"<<q.error/q.value<<"\t"<<pow(pow((q.value-1.604)/q.error,2),0.5)<<endl;
	
	classes=new measure[numofclasses];
	j=0;
	int k;
	for(int i=0;i<numofclasses;i++){
		k=charges[j].classnum;
		classes[i].value=0;
		classes[i].error=0;
		classes[i].classnum=charges[j].classnum;
		double denom=0;
		
		while(charges[j].classnum==k){
			classes[i].value=classes[i].value+k*charges[j].value/
							(pow(charges[j].error,2));
			denom=denom + 1/(pow(charges[j].error,2));
			classes[i].error=classes[i].error+pow(charges[j].error,-2);
			j++;
		}
		
		classes[i].value=classes[i].value/denom;
		classes[i].error=pow(classes[i].error, -0.5);
		
	}
	double xy=0;
	double x2=0;
	
	for(int i=0; i<numofclasses; i++){
		xy=xy+classes[i].value*classes[i].classnum/pow(classes[i].error,2);
		x2=x2+classes[i].classnum*classes[i].classnum/pow(classes[i].error,2);
	}
	q.value=xy/x2;
	q.error=0;
	for(int i=0; i<numofclasses; i++){
		q.error=q.error+pow(classes[i].error*((classes[i].value/pow(classes[i].error,2))/x2),2);
	}
	q.error=sqrt(q.error);
	
	outFile<<"Metodo regressione"<<endl;
	outFile<<"Value \t Error \t Relative error \t z"<<endl;
	outFile<<q.value<<"\t"<<q.error<<"\t"<<q.error/q.value<<"\t"<<pow(pow((q.value-1.604)/q.error,2),0.5)<<endl;
	

	q=sums(charges,count,q.value, q.error,true,0.001);

	measure qerrsx,qerrdx;
	q.error=0;
	for(int i=0;i<count;i++){
		q.error+=pow(charges[i].error/(charges[i].classnum),2);
	}
	q.error=pow(q.error,0.5);
	qerrsx=qerror(charges,count,q.value+0.1, 0.5, q.error, true, 0.0001);

	qerrdx=qerror(charges,count,q.value-0.1, 0.5, q.error, false, 0.0001);

	q.error=pow(pow(qerrsx.value-qerrdx.value,2),0.5)/2;

	outFile<<"Metodo minimi"<<endl;
	outFile<<"Value \t Error \t Relative error \t z"<<endl;
	outFile<<q.value<<"\t"<<q.error<<"\t"<<q.error/q.value<<"\t"<<pow(pow((q.value-1.604)/q.error,2),0.5)<<endl;;
	return 0;
}