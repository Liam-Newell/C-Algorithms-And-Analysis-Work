/***********************************************************/
/*                                                         */
/*   Written by: Catherine Leung                           */
/*   Version 1.0                                           */
/*   Tester for a1q2                                       */
/*                                                         */
/*   To compile:                                           */
/*     g++ poly.cpp polytester.cpp -std=c++0x              */
/*                                                         */
/*   To run:                                               */
/*     ./a.out                                             */
/*                                                         */
/***********************************************************/

#include "poly.h"
#include <iostream>

int GCD(int, int);
int main(int argc, char* argv[]) {

	int gcdResults[10] = { 5,4,50,9,21,66,5,1,10,682176 };
	int gcdPair[10][2]{ { 0,5 },{ 4,0 },{ 150,250 },{ 405,99 },{ 819,1029 },
	{ 462,660 },{ 5,5 },{ 1,1 },{ 1800,1430 },{ 310390080,21147456 } };
	int data1[4][3] = { { 3,1,4 },{ 2,1,3 },{ -1,1,1 },{ 5,1,0 } };
	int data2[4][3] = { { 2,1,2 },{ -1,1,1 },{ -1,1,0 } };
	int data3[4][3] = { { 3,2,2 },{ 7,4,1 },{ 13,8,0 } };
	int data4[4][3] = { { 19,8,1 },{ 53,8 } };
	int data5[4][3] = { { 2,1,2 },{ -1,1,1 },{ -1,1,0 } };
	int data6[4][3] = { { 1,1,0 } };

	Polynomial p1(data1, 4);
	Polynomial p2(data2, 3);
	Polynomial p3;


	Polynomial result1(data3, 3);
	Polynomial result2(data4, 2);
	Polynomial result3;
	Polynomial result4(data5, 3);
	Polynomial result5(data6, 1);
	Polynomial result6;
	Polynomial temp;
	bool gcdError = false;

	for (int i = 0; !gcdError && i<10; i++) {
		if (GCD(gcdPair[i][0], gcdPair[i][1]) != gcdResults[i]) {
			std::cout << "Error: GCD(" << gcdPair[i][0] << "," << gcdPair[i][1] << ") should be: " << gcdResults[i] << std::endl;
			gcdError = true;
		}
	}
	if (!gcdError) {
		std::cout << "GCD() is working" << std::endl;
	}
	else {
		std::cout << "Error in GCD() function" << std::endl;
	}


	if (!gcdError) {
		bool error = false;
		p3 = p1 / p2;
		if (!(p3 == result1)) {
			error = true;
			std::cout << "Error" << std::endl;
			std::cout << "(" << p1 << ") / (" << p2 << ") = " << std::endl;
			//p3 = 1 1/2 x^2 + 1 3/4 x + 1 5/8
			std::cout << result1 << std::endl;
			std::cout << "your result:" << p3 << std::endl;
		}

		if (!error) {
			p3 = p1%p2;
			if (!(p3 == result2)) {
				error = true;
				std::cout << "Error" << std::endl;
				std::cout << "(" << p1 << ") % (" << p2 << ") = " << std::endl;
				//p3 = 2 3/8 x + 6 5/8
				std::cout << result2 << std::endl;

				std::cout << "your result:" << p3 << std::endl;
			}
		}

		if (!error) {
			p3 = p2 / p1;
			if (!(p3 == result3)) {
				temp = result3;
				result3.addTerm(Fraction(0, 1), 0);
				if (!(p3 == result3)) {
					error = true;
					std::cout << "Error" << std::endl;
					std::cout << "(" << p2 << ") / (" << p1 << ") = " << std::endl;
					//p3 = 0
					std::cout << temp << std::endl;

					std::cout << "your result:" << p3 << std::endl;
				}
			}
		}

		if (!error) {
			p3 = p2%p1;
			if (!(p3 == result4)) {
				error = true;
				std::cout << "Error" << std::endl;
				std::cout << "(" << p2 << ") % (" << p1 << ") = " << std::endl;
				//p3 = 2 x^2 + -1 x + -1
				std::cout << result4 << std::endl;

				std::cout << "your result:" << p3 << std::endl;
			}
		}

		if (!error) {
			p3 = p1 / p1;
			if (!(p3 == result5)) {
				error = true;
				std::cout << "Error" << std::endl;
				std::cout << "(" << p1 << ") / (" << p1 << ") = " << std::endl;
				//p3 = 1
				std::cout << result5 << std::endl;

				std::cout << "your result:" << p3 << std::endl;
			}
		}


		if (!error) {
			p3 = p1%p1;
			if (!(p3 == result6)) {
				temp = result6;
				result6.addTerm(Fraction(0, 1), 0);
				if (!(p3 == result6)) {
					error = true;
					std::cout << "Error" << std::endl;
					std::cout << "(" << p1 << ") % (" << p1 << ") = " << std::endl;
					//p3 = 0
					std::cout << temp << std::endl;

					std::cout << "your result:" << p3 << std::endl;
				}
			}
		}
		if (error) {
			std::cout << "There is an error with your / and/or % operator" << std::endl;
		}
		else {
			std::cout << "Your / and % operator looks to be working" << std::endl;
		}
	}

	return 0;
}
