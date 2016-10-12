// Program fot data analysis of Millikan's experiment
#include<iostream>
#include<fstream>
#include<cmath>
#include <sstream>
#include "lib.h"
double average(double* , int );
double stdDevS(double* ,int);
void compat(double* values, double * errors, int number);
measure dropanalysis(ifstream &inFile, int filecount){
	//Initial Calls
	drop expDrop;
	double tester, dz, eta,b=8.2E-3,p=1.01E+5,g=9.806,dRho=858.7,t,d,dV,chi2=0;
	int count1=0, count2=0, count3=0;
	expDrop.dt1=new double[count1];
	expDrop.dt2=new double[count2];
	expDrop.dt3=new double[count3];
	ofstream outFile;
	/*
		All data must come from a txt file called data.
		Data should be organized in one column.
		
		The first data to show up must be the time intervals measured between a movement dz,
		which is to be stated later on.
		
		In particular the first set of time measurements should be of the drop falling.
		A -1 should be placed after this.
		The second set of time intervals should be of the drop rising.
		A -1 should be placed after this.
		The last set of time intervals should be of the drop falling again.
		A -1 should be placed after this. 
		
		The measure of a single dz in meters should be placed afterwards.
	
		The temperature t(in celsius) should follow then.
		
		Then d and then dV
		
	*/
	
	//Data entry
	//First fall V=0
	inFile>>tester;
	while(tester>0){

		double* temp=new double[count1+1];
		for(int i=0;i<count1;i++){
			temp[i]=expDrop.dt1[i];
		}
		delete expDrop.dt1;
		expDrop.dt1=temp;
		count1++;
		
		expDrop.dt1[count1-1]=tester;
		inFile>>tester;
	}
	for	(int i=count1-1;i>0;i--){
		expDrop.dt1[i]=expDrop.dt1[i]-expDrop.dt1[i-1];
	}
	//Rise V>0

	inFile>>tester;
	while(tester>0){

		double* temp=new double[count2+1];
		for(int i=0;i<count2;i++){
			temp[i]=expDrop.dt2[i];
		}
		delete expDrop.dt2;
		expDrop.dt2=temp;
		count2++;
		
		expDrop.dt2[count2-1]=tester;
		inFile>>tester;
	}
	for	(int i=count2-1;i>0;i--){
		expDrop.dt2[i]=expDrop.dt2[i]-expDrop.dt2[i-1];
	}
	//Second fall V<0

	inFile>>tester;
	while(tester>0){

		double* temp=new double[count3+1];
		for(int i=0;i<count3;i++){
			temp[i]=expDrop.dt3[i];
		}
		delete expDrop.dt3;
		expDrop.dt3=temp;
		count3++;
		
		expDrop.dt3[count3-1]=tester;
		inFile>>tester;
	}
	for	(int i=count3-1;i>0;i--){
		expDrop.dt3[i]=expDrop.dt3[i]-expDrop.dt3[i-1];
	}
	inFile>>dz;
	inFile>>t;
	inFile>>d;
	inFile>>dV;
	
	
	//Speed derivation;
	expDrop.v1=new double[count1];
	for(int i=0;i<count1;i++){
	expDrop.v1[i]=dz/expDrop.dt1[i];
	}
	expDrop.mv1=average(expDrop.v1,count1);
	expDrop.sv1=stdDevS(expDrop.v1, count1);

	
	expDrop.v2=new double[count2];
	for(int i=0;i<count2;i++){
	expDrop.v2[i]=dz/expDrop.dt2[i];
	}
	expDrop.mv2=average(expDrop.v2,count2);
	expDrop.sv2=stdDevS(expDrop.v2, count2);

	
	expDrop.v3=new double[count3];
	for(int i=0;i<count3;i++){
	expDrop.v3[i]=dz/expDrop.dt3[i];
	}
	expDrop.mv3=average(expDrop.v3,count3);
	expDrop.sv3=stdDevS(expDrop.v3, count3);

	
	//Eta derivation
	eta=(1.8+(t-15)*4.765e-3)*1e-5;
	
	
	//Radius estimation
	
	expDrop.r=new double[count1];
	expDrop.sr=new double[count1];
	
	for(int i=0; i<count1; i++){
		expDrop.r[i]=-b/(2*p)+sqrt(pow(b/(2*p),2)+9*eta*expDrop.v1[i]/(2*g*dRho));
		expDrop.sr[i]=9*eta*expDrop.sv1/(4*g*dRho*(expDrop.r[i]));
	}

	expDrop.mr=average(expDrop.r,count1);
	
	expDrop.msr=0;
	for(int i=0; i<count1; i++){
		expDrop.msr=expDrop.msr+pow(expDrop.sr[i],-2);
	}
	
	expDrop.msr=pow(expDrop.msr,-0.5);
	
	//Charge estimation
	expDrop.Q=new double[count2+count3];
	expDrop.sQ=new double[count2+count3];
	for(int i=0; i<count2; i++){
		expDrop.Q[i]=(-4*M_PI/3)*dRho*g*d/dV*pow(expDrop.mr,3)*(1-expDrop.v2[i]/expDrop.mv1);
		expDrop.sQ[i]=(4*M_PI/3)*dRho*g*d/dV*pow(
					pow(3*pow(expDrop.mr,2)*(1-expDrop.v2[i]/expDrop.mv1)*(expDrop.msr),2)+
					pow(pow(expDrop.mr,3)/expDrop.mv1*expDrop.sv2,2)+
					pow(pow(expDrop.mr,3)*expDrop.v2[i]/pow(expDrop.mv1,2)*expDrop.sv1,2),0.5);
	}
	//calcolo di q per ogni velocità
	for(int i=0; i<count3; i++){
		expDrop.Q[i+count2]=(4*M_PI/3)*pow(expDrop.mr,3)*dRho*g*d/dV*(1+expDrop.v3[i]/expDrop.mv1);
		expDrop.sQ[i+count2]=(4*M_PI/3)*dRho*g*d/dV*pow(
					pow(3*pow(expDrop.mr,2)*(1+expDrop.v2[i]/expDrop.mv1)*(expDrop.msr),2)+
					pow(pow(expDrop.mr,3)/expDrop.mv1*expDrop.sv2,2)+
					pow(pow(expDrop.mr,3)*expDrop.v2[i]/pow(expDrop.mv1,2)*expDrop.sv1,2),0.5);
	}
	
	measure c;
	c.number=filecount;
	//Media dei q (non pesata) ed errore
	c.value=average(expDrop.Q,count2+count3);
	c.error=0;
	for(int i=0; i<count2+count3; i++){
		c.error=c.error+pow(expDrop.sQ[i],-2);
	}
	c.error=pow(c.error,-0.5);
	//Chi^2
	
	for(int i=0;i<count2+count3;i++){
		chi2=chi2+pow(expDrop.Q[i]-c.value,2);
	}
		chi2=chi2/((count1+count2-1)*c.error*c.error);
	
	
	//Data exit
	
	//	times
	ostringstream s;
	s << "timeIntervals" << filecount <<".txt";
	string name(s.str());
	s.str("");
	outFile.open(name.c_str());
	name="";
	for(int i=0; i<count1 ; i++){
		outFile<<expDrop.dt1[i]<<endl;
	}
	outFile<<endl;

	for(int i=0; i<count2 ; i++){
		outFile<<expDrop.dt2[i]<<endl;
	}
	outFile<<endl;

	for(int i=0; i<count3 ; i++){
		outFile<<expDrop.dt3[i]<<endl;
	}

	outFile.close();
	//	speeds
	s << "speedValues" << filecount <<".txt";
	name=s.str();
	s.str("");
	outFile.open(name.c_str());
	name="";
	for(int i=0; i<count1 ; i++){
		outFile<<expDrop.v1[i]<<endl;
	}
	outFile<<endl;

	for(int i=0; i<count2 ; i++){
		outFile<<expDrop.v2[i]<<endl;
	}
	outFile<<endl;

	for(int i=0; i<count3 ; i++){
		outFile<<expDrop.v3[i]<<endl;
	}

	outFile.close();
	
	//	radii
	s << "radiiValues" << filecount <<".txt";
	name=s.str();
	s.str("");
	s.str("");
	outFile.open(name.c_str());
	name="";
	for(int i=0; i<count1 ; i++){
		outFile<<expDrop.r[i]<<endl;
	}
	outFile.close();
	
	//	Charge
	s << "chargeValues" << filecount <<".txt";
	name=s.str();
	s.str("");
	outFile.open(name.c_str());	
	name="";
	for(int i=0; i<count2+count3; i++){
		outFile<<i+1<<"\t"<<expDrop.Q[i]<<endl;
	}
	outFile.close();
	
	return c;
}