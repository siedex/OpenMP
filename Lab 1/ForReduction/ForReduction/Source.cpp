#include <omp.h>
#include <iostream>

int main() 
{
	float a[100], b[100];
	int n = 100;
	int chunk = 10;
	

	for (int i = 0; i < n; i++)
	{
		a[i] = i;
		b[i] = 2 * i;
	}

	float result = 0;
	#pragma omp parallel for default(shared) schedule(static, chunk) reduction(+:result)
	for (int i = 0; i < n; i++)
	{
		result += (a[i] * b[i]);
	}

	std::cout << "Final result = " << result << std::endl;
	getchar();
}