#include <iostream>

unsigned int factorial(unsigned int n)
{
	unsigned int rm = 1;

	if (n > 1)
		rm = n*factorial(n - 1);
	return rm;
}
double power(double base, unsigned int n)
{
	int total = 0;
	if (n > 0)
		total += base * power(base, (n - 1));
	else
		return 1;
	return total;
	/*
	if (n == 0) return 1;
	int j = base;
	for (size_t i = 1; i < n; i++)
		base = j * base;
	return base;*/
}
unsigned int fibonacci(unsigned int n)
{
	int k = 1;
	if (n == 1)
		return 1;
	if (n == 0)
		return 0;
	return fibonacci(n - 1) + fibonacci(n - 2);
	
	/*
	int j = 0;
	int k = 1;
	int r = 0;
	if (n == 1)
		n++;
	for (size_t i = 1; i < n; i++)
	{
		r = j + k;
		j = k;
		k = r;
	}

	return r;*/
}
//int main() {
//	std::cout << "Factorial: " << factorial(8) << std::endl
//		<< "Power: " << power(10,2) << std::endl
//		<< "Fibonacci: " << fibonacci(10);
//	
//}
