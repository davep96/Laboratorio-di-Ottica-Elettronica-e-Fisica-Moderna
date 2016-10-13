#include <iostream>

using namespace std;


int falsefact(int n){
	if(n==1){
		return 1;
	} else {
		return n+falsefact(n-1);
	}
}