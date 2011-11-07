
#include <math.h>
#define N	100
#define EPSILON 0.01

int main (int argc, char *argv[])
{
	double diff;	//Change in value
	int i, j;
	double mean;	//Average boundary values
	double u[N][N]; //Old Values
	double w[N][N];	//New Values
	int iters = 0;
	int k = 0;

	int rank, p;
	// Initialize MPI
	MPI_Init(&argc, &argv);
	
	// Get the rank of the curren process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Get the total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// NEW CODE

	//Number of inner loop iterations.  Put loop around next[i,j]=(old[i-1,j...)*.25;
	int iters_per_cell = (argc > 1) ? atoi(argv[1]) : 1;
	//Number of iterations, same as before
	int iterations = (argc > 2) ? atoi(argv[2]) : 100;
	//How many ghost cell layers to send at a time & how many internal iterations to perform
	//per communication
	int boundary_thickness = (argc > 3) ? atoi(argv[3]) : 1;
	//Note: Ghost Cells are memory locations used to store redundant copies of 
	//data held by neighboring processes

	//Now we determine the range of cells for each process




	//Set boundary values and compute mean boundary values
	mean = 0.0;
	for (i=0; i < N; i++)
	{
		u[i][0] = u[i][N-1] = u[0][i] = 100.0;
		u[N-1][i] = 0.0;
		mean += u[i][0] + u[i][N-1] + u[0][i] + u[N-1][i];
	}
	mean /= (4.0 * N);


	//Initialize interior values
	for (i=1; i < N-1; i++)
		for (j=1; j < N-1; j++) u[i][j] = mean;

	//Compute steady state solution
	for (k = 0; k < iterations; k++) {
		diff = 0.0;
		for (i = 1; i < N-1; i++)
		{
			for (j = 1; j < N-1; j++)	
			{
				for (iters = 0; iters < iters_per_cell; iters++)
				{
					w[i][j] = (u[i-1][j] + u[i+1][j] +
								u[i][j-1] + u[i][j+1])/4.0;
				}
			}
		}

		for (i = 1; i < N-1; i++)
			for (j=1; j < N-1; j++) u[i][j] = w[i][j];
	}

	//Print Solution
	for (i=0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf ("%6.2f ", u[i][j]);
		puchar('\n');
	}
}






/*
	// NEW CODE

	//Number of inner loop iterations.  Put loop around next[i,j]=(old[i-1,j...)*.25;
	int iters_per_cell = (argc > 1) ? atoi(argv[1]) : 1;
	//Number of iterations, same as before
	int iterations = (argc > 2) ? atoi(argv[2]) : 100;
	//How many ghost cell layers to send at a time & how many internal iterations to perform
	//per communication
	int boundary_thickness = (argc > 3) ? atoi(argv[3]) : 1;
	//Note: Ghost Cells are memory locations used to store redundant copies of 
	//data held by neighboring processes

	//END NEW CODE
	*/