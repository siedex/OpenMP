#include "stdafx.h"
#include <string>

void Task10(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Need rank as argument. Terminating.\n");
		return;
	}

	std::string str = argv[1];
	int userRank = std::stoi(str, nullptr);

	int  numtasks, rank, rc;
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (userRank > numtasks - 1)
	{
		printf("Requested rank is too high. Terminating.\n");
		MPI_Finalize();
		return;
	}

	int* receivedRanks = NULL;
	if (rank == userRank)
		receivedRanks = new int[numtasks];

	MPI_Gather(&rank, 1, MPI_INT, // Send to root
		receivedRanks, 1, MPI_INT, // Receive to
		userRank, // Root
		MPI_COMM_WORLD);

	if (rank == userRank)
	{
		printf("My rank is %d\nReceived ints:\n", rank);
		for (int i = 0; i < numtasks; i++)
		{
			if(i != rank)
				printf("%d\n", receivedRanks[i]);
		}
	}

	MPI_Finalize();
}