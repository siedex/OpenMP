#include "Header.h"

void MultiplicateVectorMatrix(double** matrix, double* vector, int n, int m, bool useOmp);

void LaunchVectorMultiplication(int n, int m, bool useOmp)
{
	if (useOmp)
		Log("Vector Matrix Multiplication                                      OMP ON");
	else
		Log("Vector Matrix Multiplication                                        OMP OFF");

	Log("------------------------------------------------------------------------------");
	Log("Matrix: " + to_string(n) + " x " + to_string(m));

	double** matrix = RandomMatrix(n, m);
	double* vector = RandomArray(n);
	
	MultiplicateVectorMatrix(matrix, vector, n, m, useOmp);

	DeallocateMatrix(matrix, n, m);
	delete[] vector;

	Log("------------------------------------------------------------------------------");
}

void MultiplicateVectorMatrix(double** matrix, double* vector, int n, int m, bool useOmp)
{
	Log("Starting calculations...");
	System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();

	watch->Start();

	#pragma omp parallel if (useOmp)
	{
		#pragma omp for 
		for (int i = 0; i < n; i++)
		{
			double sum = 0;
			for (int j = 0; j < m; j++)
			{
				sum += matrix[i][j] * vector[i];
			}

			vector[i] = sum;
		}
	}

	Log("Time ellapsed: " + to_string(watch->ElapsedTicks));
	watch->Reset();
}