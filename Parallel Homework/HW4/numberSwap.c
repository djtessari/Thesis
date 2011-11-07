#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	// Initialize MPI
	MPI_Init(&argc, &argv);
	
	// Get the rank of the current process
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Get a random number
	FILE *urandom_file = fopen("/dev/urandom","r");
	srand(getc(urandom_file));
	int my_num = rand() % 100;
	
	// Print the random number
	printf("Process %d sending %d\n", rank, my_num);
	fflush(NULL);
	 int source, int tag, MPI_Comm comm, MPI_Status *stat);
	
	// Swap random numbers with the other process
	int other_num;
	MPI_Status status;
	if (rank == 0) {
		MPI_Send(&my_num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&other_num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
	} else if (rank == 1) {
		MPI_Recv(&other_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Send(&my_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	
	printf("Process %d received %d\n", rank, other_num);
	fflush(NULL);
	
	// Clean up
	MPI_Finalize();
	
	return 0;
}
