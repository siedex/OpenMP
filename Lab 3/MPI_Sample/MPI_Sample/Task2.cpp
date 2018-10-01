#include "stdafx.h"

void Task2(int argc, char* argv[])
{
	int  numtasks, rank, rc;
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
		printf("Root process: Hello, world\n");
	else
		printf("Slave process: my rank is %d\n", rank);

	MPI_Finalize();
}