#include <omp.h>
#include <iostream>

#define N 1000

int main()
{
	float a[N], b[N], c[N], d[N];

	for (int i = 0; i < N; i++)
	{
		a[i] = i * 1.5;
		b[i] = i + 22.35;
	}

	#pragma omp parallel shared(a, b, c, d)
	{
		#pragma omp sections nowait
		{
			#pragma omp section
			for (int i = 0; i < N; i++)
				c[i] = a[i] + b[i];

			#pragma omp section
			for (int i = 0; i < N; i++)
				d[i] = a[i] * b[i];
		}
	}
}