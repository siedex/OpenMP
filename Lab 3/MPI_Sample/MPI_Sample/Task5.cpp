#include "stdafx.h"

void Task5(int argc, char* argv[], int n)
{
	int numtasks, rank, rc, tag = 1;
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
		double* arr = СreateArray(n);

		printf("============================================MPI ON\n");
		printf("Length: %d\n", n);
		System::Diagnostics::Stopwatch^ watch = gcnew System::Diagnostics::Stopwatch();

		watch->Start();

		double sum = 0;
		if (numtasks > 1)
		{
			int index = 0;
			for (int dest = 1; dest < numtasks; dest++)
			{
				rc = MPI_Send(arr + index, parts[dest], MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
				index += parts[dest];
			}

			for (int source = 1; source < numtasks; source++)
			{
				double result = 0;
				MPI_Recv(&result, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &Stat);
				//printf("Root task received calculated sum %f from task %d\n", result, Stat.MPI_SOURCE);

				sum += result;
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				sum += arr[i];
			}
		}
		
		delete[] arr;

		printf("Result sum: %f\n", sum);
		printf("Time ellapsed: %lld\n", watch->ElapsedTicks);
		printf("=========================================================\n");

		watch->Stop();
	}
	else
	{
		int count = parts[rank];
		double* receivedArr = new double[count];
		int source = 0;

		MPI_Recv(receivedArr, count, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &Stat);

		double sum = 0;
		for (int i = 0; i < count; i++)
			sum += receivedArr[i];

		//printf("Task %d: Calculated sum %f\n", rank, sum);

		int dest = 0;
		MPI_Send(&sum, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);

		delete[] receivedArr;
	}

	MPI_Finalize();
}

double* СreateArray(int n)
{
	double* arr = new double[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = 1;
	}

	return arr;
}

