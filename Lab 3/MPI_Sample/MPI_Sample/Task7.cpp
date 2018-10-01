#include "stdafx.h"

void Task7(int argc, char* argv[], int n)
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
		double** matrix = СreateMatrix(n);
		double* vector = СreateArray(n);

		printf("===============================================MPI ON\n");
		printf("Matrix: %d x %d\n", n,n);
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
				// Send part of the vector ------------------------------------------------------------
				MPI_Send(vector + index, parts[dest], MPI_DOUBLE, dest, tagVector, MPI_COMM_WORLD);
				//-------------------------------------------------------------------------------------
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
		
		//====================================================================================
		// Receive part of the vector---------------------------------------------------------
		double* receivedVector = new double[count];
		MPI_Recv(receivedVector, count, MPI_DOUBLE, source, tagVector, MPI_COMM_WORLD, &Stat);
		//====================================================================================

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

