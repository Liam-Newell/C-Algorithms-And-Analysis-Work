#include <iostream>
unsigned int factorial(unsigned int n) 
{
	if (n > 0)
		for (size_t i = (n - 1); i > 0; i--)
			n = n * i;
	else
		return 1;
	return n;
}
double power(double base, unsigned int n) 
{
	if (n == 0) return 1;
	int j = base;
	for (size_t i = 1; i < n; i++)
		base = j * base;
	return base;
}
unsigned int fibonacci(unsigned int n) 
{
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
		
		return r;
}
//int main() {
//	std::cout << "Factorial: " << factorial(8) << std::endl
//		<< "Power: " << power(10,2 ) << std::endl
//		<< "Fibonacci: " << fibonacci(10);
//	
//}
