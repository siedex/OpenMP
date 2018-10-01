#include "stdafx.h"

double** ÑreateMatrix(int n);
void ClearMatrix(double** matrix, int n);
double* MatrixMultiplyVector(double** matrix, int n, int m, double* vector);
void ShowMatrix(double** matrix, int n, int m);
void ShowVector(double* vector, int n);

void Task6(int argc, char* argv[], int n)
{
	int numtasks, rank, rc, tagMatrix = 1, tagVector = 2;
	MPI_Status Stat;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int* parts = new int[numtasks];

	if (numtasks > 1)
	{
		int part = n / (numtasks - 1);
		for (int i = 1; i < numtasks; i++)
		{
			if (i == numtasks - 1)
				parts[i] = n - part * (i - 1);
			else
				parts[i] = part;
		}
	}

	if (rank == 0) {
		double** matrix = ÑreateMatrix(n);
		double* vector = ÑreateArray(n);

		printf("===============================================MPI ON\n");
		printf("Matrix: %d x %d\n", n, n);
		System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();

		watch->Start();

		double* resultVector = new double[n];
		if (numtasks > 1)
		{

			int index = 0;
			for (int dest = 1; dest < numtasks; dest++)
			{
				//rc = MPI_Send(&matrix[0][0], n, MPI_DOUBLE, dest, tagMatrix, MPI_COMM_WORLD);

				// Send parts of the matrix
				for (int i = 0; i < parts[dest]; i++)
				{
					MPI_Send(matrix[index + i], n, MPI_DOUBLE, dest, tagMatrix, MPI_COMM_WORLD);
				}

				//================================================================
				// Send full vector ----------------------------------------------
				MPI_Send(vector, n, MPI_DOUBLE, dest, tagVector, MPI_COMM_WORLD);
				//----------------------------------------------------------------
				//================================================================

				index += parts[dest];
			}

			// Receive parts of result array
			index = 0;
			for (int source = 1; source < numtasks; source++)
			{
				double* partVector = new double[parts[source]];
				MPI_Recv(partVector, parts[source], MPI_DOUBLE, source, tagVector, MPI_COMM_WORLD, &Stat);

				for (int i = 0; i < parts[source]; i++)
				{
					resultVector[index + i] = partVector[i];
				}

				index += parts[source];
			}


		}
		else
		{
			resultVector = MatrixMultiplyVector(matrix, n, n, vector);
		}

		//ShowVector(resultVector, n);

		ClearMatrix(matrix, n);
		delete[] resultVector;

		printf("Time ellapsed: %lld\n", watch->ElapsedTicks);
		printf("=========================================================\n");

		watch->Stop();
	}
	else
	{
		/*double* row = new double[n];
		MPI_Recv(row, n, MPI_DOUBLE, 0, tagMatrix, MPI_COMM_WORLD, &Stat);*/

		int count = parts[rank];
		double** receivedMatrix = new double*[count];
		int source = 0;

		// Receive part of matrix
		for (int i = 0; i < count; i++)
		{
			double* row = new double[n];
			MPI_Recv(row, n, MPI_DOUBLE, source, tagMatrix, MPI_COMM_WORLD, &Stat);
			receivedMatrix[i] = row;
		}

		//=================================================================================
		// Receive full vector ------------------------------------------------------------
		double* receivedVector = new double[n];
		MPI_Recv(receivedVector, n, MPI_DOUBLE, source, tagVector, MPI_COMM_WORLD, &Stat);
		//---------------------------------------------------------------------------------
		//=================================================================================

		//Calcualte new vector;
		double* resultVector = MatrixMultiplyVector(receivedMatrix, count, n, receivedVector);

		//Send result vector to master
		int dest = 0;
		MPI_Send(resultVector, count, MPI_DOUBLE, dest, tagVector, MPI_COMM_WORLD);


		delete[] resultVector;
		delete[] receivedVector;
		ClearMatrix(receivedMatrix, count);
	}

	MPI_Finalize();
}

void ClearMatrix(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

double** ÑreateMatrix(int n)
{
	double** table = new double*[n];
	for (int i = 0; i < n; ++i)
	{
		table[i] = new double[n];
		for (int j = 0; j < n; ++j)
		{
			table[i][j] = i;
		}
	}

	return table;
}

double* MatrixMultiplyVector(double** matrix, int n, int m, double* vector)
{
	double* resultVector = new double[n];
	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int j = 0; j < m; j++)
		{
			sum += matrix[i][j] * vector[i];
		}

		resultVector[i] = sum;
	}

	return resultVector;
}

void ShowMatrix(double** matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}

void ShowVector(double* vector, int n)
{
	for (int j = 0; j < n; j++)
	{
		printf("%f ", vector[j]);
	}
}