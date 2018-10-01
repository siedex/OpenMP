#include "Header.h"

double* RandomPositiveNegativeArray(int n);
int CountSignedValues(double* arr, int n, bool useOmp);

int LaunchCriticalSectionComparison(int n, bool useOmp)
{
	if (useOmp)
		Log("Critical Section Comparison                                              OMP ON");
	else
		Log("Critical Section Comparison                                              OMP OFF");

	Log("------------------------------------------------------------------------------");
	Log("Array length: " + to_string(n));

	double *arr = RandomPositiveNegativeArray(n);
	int result = CountSignedValues(arr, n, useOmp);
	
	/*Log("Negative values: " + to_string(result[0]));
	Log("Equal zero values: " + to_string(result[1]));
	Log("Positive values: " + to_string(result[2]));*/

	//delete[] result;
	delete[] arr;

	Log("------------------------------------------------------------------------------");

	return result;
}

int CountSignedValues(double* arr, int n, bool useOmp)
{
	int* counts = new int[3]();
	Log("Starting calculations...");
	System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();
	
	watch->Start();

	#pragma omp parallel if(useOmp)
	{
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			if (arr[i] < 0)
			{
				#pragma omp critical(name1)// только 1 потоку
				counts[0] += 1;
			}
			else if (arr[i] == 0)
			{
				#pragma omp critical(name2)
				counts[1] += 1;
			}
			else
			{
				#pragma omp critical(name3)
				counts[2] += 1;
			}
		}
	}

	int result = watch->ElapsedTicks;

	Log("Time ellapsed: " + to_string(watch->ElapsedTicks));
	watch->Reset();

	return result;
}

double* RandomPositiveNegativeArray(int n)
{
	double* arr = new double[n];
	for (int i = 0; i < n; i++)
	{
		int x = std::rand() % 3 - 1;
		arr[i] = x;
	}

	return arr;
}