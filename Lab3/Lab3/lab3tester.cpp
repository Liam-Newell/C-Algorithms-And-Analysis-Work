/************************************************************/
/*  Lab 3 tester                                            */
/*  To compile:                                             */
/*     g++ lab3tester.cpp -std=c++0x                        */
/*  To run:                                                 */
/*     ./a.out                                              */
/************************************************************/

#include "lab3.h"
#include <iostream>

int main(void){
	SList<int> singly;
	Sentinel<int> sentinel;

	std::cout << "testing singly linked list" << std::endl;


	for(int i=0;i<3;i++){
		singly.push_front(i);
		singly.print();
	}
	for(int i=3;i<6;i++){
		singly.push_back(i);
		singly.print();
	}
	for(int i=0;i<7;i++){
		if(i%2){
			singly.pop_front();
		}
		else{
			singly.pop_back();
		}
		singly.print();
	}
	for(int i=0;i<3;i++){
		singly.push_back(i);
		singly.print();
	}
	for(int i=3;i<6;i++){
		singly.push_front(i);
		singly.print();
	}
	for(int i=0;i<7;i++){
		if(i%2==0){
			singly.pop_front();
		}
		else{
			singly.pop_back();
		}
		singly.print();
	}
	for(int i=0;i<3;i++){
		singly.push_front(i);
		singly.print();
	}	

	std::cout << "testing sentinel list" << std::endl;

	for(int i=0;i<3;i++){
		sentinel.push_front(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=3;i<6;i++){
		sentinel.push_back(i);
		sentinel.print();
	}
	sentinel.reversePrint();

	for(int i=0;i<7;i++){
		if(i%2){
			sentinel.pop_front();
		}
		else{
			sentinel.pop_back();
		}
		sentinel.print();
	}
	sentinel.reversePrint();

	for(int i=0;i<3;i++){
		sentinel.push_back(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=3;i<6;i++){
		sentinel.push_front(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=0;i<7;i++){
		if(i%2==0){
			sentinel.pop_front();
		}
		else{
			sentinel.pop_back();
		}
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=0;i<3;i++){
		sentinel.push_front(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	return 0;
}
