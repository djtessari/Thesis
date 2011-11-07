#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
	int rank, p;

	// Initialize MPI
	MPI_Init(&argc, &argv);
	
	// Get the rank of the curren process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Get the total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	printf("Hello from process %d/%d\n", rank, p);
	fflush(NULL);  // Flush all of the output streams
	
	// Clean up
	MPI_Finalize();
	
	return 0;
}