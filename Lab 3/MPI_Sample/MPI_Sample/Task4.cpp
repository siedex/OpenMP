#include "stdafx.h"

void Task4(int argc, char* argv[])
{
	int numtasks, rank, rc, tag = 1;

	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (int dest = 1; dest < numtasks; dest++)
		{
			char msg = 'a' + (dest - 1);
			rc = MPI_Send(&msg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
		}
		
		for (int source = 1; source < numtasks; source++)
		{
			char msg;
			MPI_Recv(&msg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);

			printf("Root task received '%c' from task %d\n", msg, Stat.MPI_SOURCE);
		}
	}
	else
	{
		char msg;
		int source = 0;
		MPI_Recv(&msg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
		printf("Task %d: Received '%c' from task %d\n", rank, msg, Stat.MPI_SOURCE);

		MPI_Send(&msg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD);
	}
		
	MPI_Finalize();
}

