#include "stdafx.h"

#define NPROCS 12

void Lab4_1(int argc, char* argv[])
{
	int        rank, rankGroup1, rankGroup2, numtasks;
	int        ranksGroup1[] = { 0,1,2,3,4,5 }, ranksGroup2[] = { 6,7,8,9,10,11 };//массивы с рангами
	MPI_Group  orig_group, group1, group2;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (numtasks != NPROCS) {//проверка наличия необходимого числа процессов
		printf("Must specify MP_PROCS= %d. Terminating.\n", NPROCS);
		MPI_Finalize();
		return;
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);//определение рангов в MPI_COMM_WORLD

	MPI_Comm_group(MPI_COMM_WORLD, &orig_group);//создание исходной группы

	// Create group1 using ranks from ranksGroup1
	MPI_Group_incl(orig_group, 6, ranksGroup1, &group1);
	// Create group2 using ranks from ranksGroup2
	MPI_Group_incl(orig_group, 6, ranksGroup2, &group2);

	MPI_Group_rank(group1, &rankGroup1);//определение новых рангов в new_group1
	MPI_Group_rank(group2, &rankGroup2);

	MPI_Comm comm1, comm2;

	// Create new communicator comm1 from group1
	MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
	// Create new communicator comm2 from group2
	MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);

	if (rankGroup1 != MPI_UNDEFINED)
		printf("old rank = %d ; Group %d new rank = %d\n", rank, 1, rankGroup1);

	if (rankGroup2 != MPI_UNDEFINED)
		printf("old rank = %d ; Group %d new rank = %d\n", rank, 2, rankGroup2);

	if (rankGroup1 != MPI_UNDEFINED)
	{
		//MPI_Intercomm_create(comm1, 0, MPI_COMM_WORLD, 0, 1, &intercom);

		int x = rank;
		int result = 0;
		MPI_Reduce(&x, &result, 1, MPI_INT, MPI_MAX, 0, comm1);

		if (rank == 0)
			printf("Process with rank %d says: MAX_RANK: %d", rank, result);

		MPI_Comm_free(&comm1);
		MPI_Group_free(&group1);
	}
	else if (rankGroup2 != MPI_UNDEFINED)
	{
		int x = rank;
		int result = 0;
		MPI_Reduce(&x, &result, 1, MPI_INT, MPI_MIN, 5, comm2);

		if (rank == 11)
			printf("Process with rank %d says MIN_RANK : %d", rank, result);

		MPI_Comm_free(&comm2);
		MPI_Group_free(&group2);
	}

	MPI_Finalize();
}