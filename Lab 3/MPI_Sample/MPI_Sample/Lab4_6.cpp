#include "stdafx.h"
#include <string>

#define SIZE 5

using namespace std;

string int_array_to_string(int int_array[], int size_of_array);

void Lab4_6(int argc, char*argv[])
{
	int numtasks;
	int node;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	int index[] = { 2,4,6,8,10 };
	int edges[] = { 2,3,3,4,0,4,1,0,1,2 };

	if (numtasks == SIZE) 
	{
		MPI_Comm graphComm;
		MPI_Graph_create(MPI_COMM_WORLD, SIZE, index, edges, 1, &graphComm);

		MPI_Comm_rank(graphComm, &node);

		int nCount;
		MPI_Graph_neighbors_count(graphComm, node, &nCount);

		int* neigbors = new int[nCount];
		MPI_Graph_neighbors(graphComm, node, nCount, neigbors);

		string arrayStr = int_array_to_string(neigbors, nCount);
		printf("Node %d has %d neighbors: { %s }", node, nCount, arrayStr.c_str());

		delete[] neigbors;
	}
	else
		printf("Must specify %d processors. Terminating.\n", SIZE);

	MPI_Finalize();
}

string int_array_to_string(int int_array[], int size_of_array) 
{
	string returnstring = "";

	
	for (int temp = 0; temp < size_of_array; temp++)
	{
		char buffer[100];
		sprintf_s(buffer, "%d", int_array[temp]);
		
		returnstring += string(buffer);

		if (temp < size_of_array - 1)
			returnstring += ", ";
	}
		
	return returnstring;
}
