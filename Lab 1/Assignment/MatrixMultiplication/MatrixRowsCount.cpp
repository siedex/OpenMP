#include "Header.h"

int CountMatrixRows(double** matrix, int n, int m, bool useOmp);

void LaunchMatrixRowsCount(int n, int m, bool useOmp)
{
	if (useOmp)
		Log("Matrix Rows Count                                       OMP ON");
	else
		Log("Matrix Rows Count                                        OMP OFF");

	Log("------------------------------------------------------------------------------");
	Log("Matrix: " + to_string(n) + " x " + to_string(m));

	double** matrix = RandomZeroOneMatrix(n, m);

	Log("Result: " + to_string(CountMatrixRows(matrix, n, m, useOmp)));

	DeallocateMatrix(matrix, n, m);

	Log("------------------------------------------------------------------------------");
}

int CountMatrixRows(double** matrix, int n, int m, bool useOmp)
{
	Log("Starting calculations...");
	System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();
	int count = 0;

	watch->Start();

	#pragma omp parallel if (useOmp) shared(count)
	{
		#pragma omp parallel for reduction(+:count)
		for (int i = 0; i < n; i++)
		{
			if (matrix[i][i] == 0)
			{
				count++;
			}
		}
	}

	Log("Time ellapsed: " + to_string(watch->ElapsedTicks));
	watch->Reset();

	return count;
}