#include "Header.h"

double MinValue(double* arr, int n, bool useOmp);

void LaunchMinSearch(int n, bool useOmp)
{
	if (useOmp)
		Log("Matrix Value                                       OMP ON");
	else
		Log("Matrix Value                                        OMP OFF");

	Log("------------------------------------------------------------------------------");
	Log("Array length: " + to_string(n));

	double* arr = RandomArray(n);

	Log("Result: " + to_string(MinValue(arr, n, useOmp)));

	delete[] arr;

	Log("------------------------------------------------------------------------------");
}

double MinValue(double* arr, int n, bool useOmp)
{
	System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();
	watch->Start();

	double min = arr[0];
	#pragma omp parallel shared(min)
	{
		#pragma omp for
		for (int i = 0; i < n; ++i)
		{
			#pragma omp flush(min)//obnovlyaet zna4eie peremennoi
			if (arr[i] < min)
			{
				#pragma omp critical
				{
					if (arr[i] < min) min = arr[i];
				}
			}
		}
	}
	
	Log("Time ellapsed: " + to_string(watch->ElapsedTicks));
	watch->Reset();

	return min;
}