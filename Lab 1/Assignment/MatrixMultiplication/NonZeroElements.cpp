#include "Header.h"
using namespace std;

int CountNonZeroValues(double** matrix, int n, int m, bool useOmp);

void LaunchNonZeroSelection(int n, int m, bool useOmp)
{
	if (useOmp)
		Log("Non Zero Selection                                        OMP ON");
	else
		Log("Non Zero Selection                                        OMP OFF");
	Log("------------------------------------------------------------------------------");
	Log("Matrix: " + to_string(n) + " x " + to_string(m));

	double** matrix = RandomZeroOneMatrix(n, m);

	Log("Result: " + to_string(CountNonZeroValues(matrix, n, m, useOmp)));

	DeallocateMatrix(matrix, n, m);

	Log("------------------------------------------------------------------------------");
}

double** RandomZeroOneMatrix(int n, int m)
{
	Log("Creating matrix...");
	double** matrix = new double*[n];
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			matrix[i][j] = std::rand() % 2;
		}
	}

	return matrix;
}

int CountNonZeroValues(double** matrix, int n, int m, bool useOmp)
{
	Log("Starting calculations...");
	System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();
	

	int count = 0;

	int maxThreadsNum = omp_get_max_threads();
	list<double>* vectors = new list<double>[maxThreadsNum];
	
	watch->Start();
		 
	for (int i = 0; i < n; i++)
	{
		#pragma omp parallel if (useOmp) 
		{
			#pragma omp for reduction(+:count) nowait
			for (int j = 0; j < m; j++)
			{
				if (matrix[i][j] != 0)
				{
					count++;
					int threadsIndex = omp_get_thread_num();

					/*if(vectors[threadsIndex].size() < vectors[threadsIndex].max_size() - 50)
						vectors[threadsIndex].push_back(matrix[i][j]);*/
				}
			}
		}
	}

	Log("Time ellapsed: " + to_string(watch->ElapsedTicks));
	watch->Reset();

	list<double>* result = &vectors[0];
	for (int i = 1; i < omp_get_max_threads(); i++)
	{
		result->insert(result->end(), vectors[i].begin(), vectors[i].end());
	}


	delete[] vectors;

	

	return count;
}