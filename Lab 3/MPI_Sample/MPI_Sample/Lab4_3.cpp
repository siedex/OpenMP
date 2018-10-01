#include "stdafx.h"

#define SIZE 16

void Lab4_3(int argc, char*argv[]) 
{
	int numtasks;
	int rank, rank1;
	int dims[2] = { 4,4 }, periods[2] = { 0,0 }, reorder = 0, coords[2];
	int left, right, top, bottom;
	MPI_Comm cartcomm;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (numtasks == SIZE) {
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm, &rank1);
		MPI_Cart_coords(cartcomm, rank, 2, coords);

		MPI_Cart_shift(cartcomm, 1, 1, &left, &right);
		MPI_Cart_shift(cartcomm, 0, 1, &top, &bottom);
		//printf("Rank %d has such coordinates: %d %d\n -> Left: %d; Right: %d Top: %d; Bottom: %d\n", rank1, coords[0], coords[1], left, right, top, bottom);

		MPI_Status status;

		int receivedRank;
		if (left != MPI_PROC_NULL)
		{
			MPI_Sendrecv(&rank1, 1, MPI_INT, left, 1, &receivedRank, 1, MPI_INT, left, 1, cartcomm, &status);
			printf("Rank %d received value %d from rank %d on the left\n", rank1, receivedRank, left);
		}
			
		if (right != MPI_PROC_NULL)
		{
			MPI_Sendrecv(&rank1, 1, MPI_INT, right, 1, &receivedRank, 1, MPI_INT, right, 1, cartcomm, &status);
			printf("Rank %d received value %d from rank %d on the right\n", rank1, receivedRank, right);
		}

		if (top != MPI_PROC_NULL)
		{
			MPI_Sendrecv(&rank1, 1, MPI_INT, top, 1, &receivedRank, 1, MPI_INT, top, 1, cartcomm, &status);
			printf("Rank %d received value %d from rank %d on the top\n", rank1, receivedRank, top);
		}

		if (bottom != MPI_PROC_NULL)
		{
			MPI_Sendrecv(&rank1, 1, MPI_INT, bottom, 1, &receivedRank, 1, MPI_INT, bottom, 1, cartcomm, &status);
			printf("Rank %d received value %d from rank %d on the bottom\n", rank1, receivedRank, bottom);
		}
			
		MPI_Barrier(cartcomm);
	}
	else
		printf("Must specify %d processors. Terminating.\n", SIZE);

	MPI_Finalize();
}
