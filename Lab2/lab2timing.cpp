/*
To compile: g++ lab2.cpp lab2timing.cpp timer.cpp
*/
#include "timer.h"
#include <iostream>
using namespace std;

unsigned int factorial (unsigned int n);
double power (double base, unsigned int n);
unsigned int fibonacci (unsigned int n);

int main(void){
	unsigned int n = 35;
	unsigned int rc;
	Timer t;
	
	int correctFactorial[13] = { 35,36,37,38,39,40,41 };
	for (auto i : correctFactorial) {
		t.reset();
		t.start();
		rc = fibonacci(i);
		t.stop();
		cout << "fibonacci (" << i << ") = " << rc << endl;
		cout << "fibonacci (" << i << ") took " << t.currtime() << " s" << endl;
	}
	
	
 	return 0;
}