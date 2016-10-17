#include <iostream>
#include <cmath>
#include "lib.h"
using namespace std;

double wdevstd(measure* a, int n){
	double std=0;
	for(int i=0; i< n; i++){
		std=std+pow(a[i].error,-2);
	}
	return pow(std,-0.5);
}