#include "Header.h"

#include <ctime>
using namespace std;

void MatrixMultiplying(int k);
void NonZeroElements();
void NumbersInBorders();
void LaunchMatrixRowsCount(int n, int m, bool useOmp);
void CountMatrixRows();
void AvgArrayNeighbours(int count);
void MultiplicateMatrixVector();

void CriticalSectionComparison();
void PairwiseSum();
void PrefixSum();
void ComplexMatrix();
void MinSearch();
void BubbleSort();


int counts[] = { 100,1000,2000,4000,6000,8000,10000, 100000, 1000000 };

int main(int argc, char* argv[])
{
	if (argc < 3) return -1;
	
	int k = stoi(string(argv[1]));
	int count = stoi(string(argv[2]));

	std::srand(unsigned(std::time(0)));

	//MatrixMultiplying(k);
	//NonZeroElements();
	//NumbersInBorders();
	//CountMatrixRows();
	//AvgArrayNeighbours(count);
	//MultiplicateMatrixVector();
	
	//CriticalSectionComparison();
	//PairwiseSum();
	PrefixSum();
	//ComplexMatrix();
	//MinSearch();
	//BubbleSort();

	getchar();
	return 0;
}

void BubbleSort()
{
	//LaunchBubbleSort(10, true);
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		double time1 = LaunchBubbleSort(counts[i], true);
		double time2 = LaunchBubbleSort(counts[i], false);

		Log("Array length: " + to_string(counts[i]));
		Log("omp off / omp on : " + to_string(time2 / time1));
		Log("==============================================================================");
	}
}

void ComplexMatrix()
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchComplexMultiplication(counts[i], true);
		LaunchComplexMultiplication(counts[i], false);
		Log("==============================================================================");
	}
}

void CriticalSectionComparison()
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		double time1 = LaunchCriticalSectionComparison(counts[i], true);
		double time2 = LaunchCriticalSectionComparison(counts[i], false);

		Log("Array length: " + to_string(counts[i]));
		Log("omp off / omp on : " + to_string(time2 / time1));
		Log("==============================================================================");
	}
}

void PrefixSum()
{
	//LaunchPrefixSum(10, true);
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		double time1 = LaunchPrefixSum(counts[i], true);
		double time2 = LaunchPrefixSum(counts[i], false);

		Log("Array length: " + to_string(counts[i]));
		Log("omp off / omp on : " + to_string(time2 / time1));
		Log("==============================================================================");
	}
}

void PairwiseSum()
{
	//LaunchPairwiseSum(100, true);
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchPairwiseSum(counts[i], true);
		LaunchPairwiseSum(counts[i], false);
		Log("==============================================================================");
	}
}


void MultiplicateMatrixVector()
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchVectorMultiplication(counts[i], counts[i], true);
		LaunchVectorMultiplication(counts[i], counts[i], false);
		Log("==============================================================================");
	}
}

void AvgArrayNeighbours(int count)
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchArrayAvgNeghbours(counts[i], count, true);
		LaunchArrayAvgNeghbours(counts[i], count, false);
		Log("==============================================================================");
	}
}

void CountMatrixRows()
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchMatrixRowsCount(counts[i], counts[i], true);
		LaunchMatrixRowsCount(counts[i], counts[i], false);
		Log("==============================================================================");
	}
}

void NumbersInBorders()
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchArrayNumbers(counts[i], true);
		LaunchArrayNumbers(counts[i], false);
		Log("==============================================================================");
	}
}

void NonZeroElements()
{
	//LaunchNonZeroSelection(4, 4, true);
	for (int i = 0; i < sizeof(counts) / sizeof (*counts); i++)
	{
		Log("==============================================================================");
		LaunchNonZeroSelection(counts[i], counts[i], true);
		LaunchNonZeroSelection(counts[i], counts[i], false);
		Log("==============================================================================");
	}
}

void MatrixMultiplying(int k)
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchMatrixCalculations(counts[i], counts[i], k, true);
		LaunchMatrixCalculations(counts[i], counts[i], k, false);
		Log("==============================================================================");
	}
}

void MinSearch()
{
	for (int i = 0; i < sizeof(counts) / sizeof(*counts); i++)
	{
		Log("==============================================================================");
		LaunchMinSearch(counts[i], true);
		LaunchMinSearch(counts[i], false);
		Log("==============================================================================");
	}
}

double MultiplyMatrix(double** matrix, int n, int m, int k, bool useOmp)
{
	double result = 0;
	double** newMatrix = CreateMatrix(n, m);

	Log("Starting calculations...");
	System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();
	watch->Start();
	
	/*int cpuCount = omp_get_max_threads();
	#pragma omp parallel if(useOmp) num_threads(cpuCount / 2)
	{
		#pragma omp for  reduction(+:result)
		for (int i = 0; i < n; i++)
		{
			#pragma omp parallel if(useOmp) shared(result) num_threads(cpuCount / 2)
			{
				#pragma omp for reduction(+:result)
				for (int j = 0; j < m; j++)
				{
					newMatrix[i][j] = matrix[i][j] * k;
					result += newMatrix[i][j];
				}
			}
		}
	}*/

	for (int i = 0; i < n; i++)
	{
		#pragma omp parallel if (useOmp) 
		{
			#pragma omp for reduction(+:result) nowait
			for (int j = 0; j < m; j++)
			{
				newMatrix[i][j] = matrix[i][j] * k;
				result += newMatrix[i][j];
			}
		}
	}

	
	Log("Time ellapsed: " + to_string(watch->ElapsedTicks));
	watch->Reset();
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << newMatrix[i][j] << " ";
		}

		cout << endl;
	}*/

	DeallocateMatrix(newMatrix, n, m);
	return result;
}

void LaunchMatrixCalculations(int n, int m, int k, bool useOmp)
{
	if(useOmp)
		Log("Matrix Multiplication                                        OMP ON");
	else
		Log("Matrix Multiplication                                        OMP OFF");
	Log("K: " + to_string(k));
	Log("------------------------------------------------------------------------------");
	Log("Matrix: " + to_string(n) + " x " + to_string(m));

	double** matrix = RandomMatrix(n, m);

	Log("Result: " + to_string(MultiplyMatrix(matrix, n, m, k, useOmp)));

	DeallocateMatrix(matrix, n, m);

	Log("------------------------------------------------------------------------------");
}

double** RandomMatrix(int n, int m)
{
	Log("Creating matrix...");
	double** matrix = new double*[n];
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			matrix[i][j] = std::rand() % 10000;
		}
	}

	return matrix;
}

double** CreateMatrix(int n, int m)
{
	Log("Creating matrix...");
	double** matrix = new double*[n];
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new double[m];
	}

	return matrix;
}

void DeallocateMatrix(double** matrix, int n, int m)
{
	Log("Deallocating matrix...");
	for (int i = 0; i < m; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

void Log(string str)
{
	ofstream logFile;
	logFile.open("log.txt", ios::app);

	cout << str << endl;
	logFile << str << endl;

	logFile.close();
}