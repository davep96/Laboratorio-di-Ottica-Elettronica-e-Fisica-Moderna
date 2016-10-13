#include <iostream>
#include <cmath>
#include "lib.h"
using namespace std;

double wave(measure* a, int n){
	double ave=0, denom=0;
	for(int i=0; i< n; i++){
		ave=ave+a[i].value*pow(a[i].error,-2);
		denom=denom+pow(a[i].error,-2);
	}
	ave=ave/denom;
	return ave;
}