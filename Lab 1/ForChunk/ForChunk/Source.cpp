#include <omp.h>
#include <iostream>

#define CHUNKSIZE 100
#define N 1000

using namespace std;

int main()
{
	float a[N], b[N], c[N];

	for (int i = 0; i < N; i++)
	{
		a[i] = b[i] = i;
	}

	#pragma omp parallel shared(a,b,c)
	{
		#pragma omp for schedule(dynamic, CHUNKSIZE) nowait
		for (int i = 0; i < N; i++)
		{
			c[i] = a[i] + b[i];
		}
	}

	for (int i = 0; i < N; i++)
	{
		cout << c[i] << endl;
	}
	getchar();
}