#include <iostream>
#include "lib.h"
using namespace std;

void scambia(measure*,measure*);

void quick(measure* vett, int n, int sx, int dx){
	int i,j;
	double m;
	i=sx;
	j=dx;
	m=(vett[sx].value+vett[dx].value)*0.5;
	do{

		while(vett[i].value<m) {
			i++;
		}
		while(m<vett[j].value) {
			j--;
		}
		if(i<=j){
			scambia(&vett[i],&vett[j]);
			i++;
			j--;
		}
		
	}while(i<=j);
	
	if(sx<j) quick(vett,n,sx,j);
	if(dx>i) quick(vett,n,i,dx);
	
	return;
}

void scambia(measure* x, measure* y){
	measure z;
	z=*x;
	*x=*y;
	*y=z;
	return;
}