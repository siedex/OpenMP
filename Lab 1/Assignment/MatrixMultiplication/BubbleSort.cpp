#include "Header.h"

int BubbleSort(double* arr, int n, bool useOmp);

int LaunchBubbleSort(int n, bool useOmp)
{
	if (useOmp)
		Log("Bubble Sort                                       OMP ON");
	else
		Log("Bubble Sort                                        OMP OFF");

	Log("------------------------------------------------------------------------------");
	Log("Array length: " + to_string(n));

	double* arr = RandomArray(n);

	int result = BubbleSort(arr, n, useOmp);

	delete[] arr;

	Log("------------------------------------------------------------------------------");

	return result;
}

int BubbleSort(double* arr, int n, bool useOmp)
{
	System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();
	watch->Start();

	/*int i, tmp, changes;
	int chunk;

	changes = 1;
	while (changes)
	{
		#pragma omp parallel if(useOmp) private(tmp)
		{
			changes = 0;
			#pragma omp for reduction(+:changes)
			for (i = 0; i < n - 1; i = i + 2)
			{
				if (arr[i] > arr[i + 1])
				{
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
					++changes;
				}
			}

			#pragma omp for reduction(+:changes)
			for (i = 1; i < n - 1; i = i + 2)
			{
				if (arr[i] > arr[i + 1])
				{
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
					++changes;
				}
			}
		}
	}*/
	for (int i = 0; i < n; i++)
	{
		int first = i % 2; // 0 if i is 0, 2, 4, ...
						   // 1 if i is 1, 3, 5, ...
		#pragma omp parallel default(none),shared(arr,first) if(useOmp)
		{
			#pragma omp for 
			for (int j = first; j < n - 1; j += 2)
			{
				if (arr[j] > arr[j + 1])
				{
					std::swap(arr[j], arr[j + 1]);
				}
			}
		}
	}

	int result = watch->ElapsedTicks;

	Log("Time ellapsed: " + to_string(watch->ElapsedTicks));
	watch->Reset();

	return result;
}