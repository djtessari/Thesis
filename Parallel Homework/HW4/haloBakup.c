
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
	int num_rows = N / p;  //Total rows over number of processes
	num_rows += boundary_thickness; //Add extra rows for ghost points
	if (rank != (p-1) && rank != 0)
		num_rows += boundary_thickness;  //Add second set if the process is not the first or last
	

	


	//Set boundary values and compute mean boundary values
	mean = 0.0;
	for (i=0; i < num_rows; i++)
	{
		u[i][0] = u[i][N-1] = u[0][i] = 100.0;
		u[num_rows-1][i] = 0.0;
		mean += u[i][0] + u[i][N-1] + u[0][i] + u[num_rows-1][i];
	}
	mean /= (4.0 * num_rows);


	//Initialize interior values
	for (i=1; i < num_rows-1; i++)
		for (j=1; j < N-1; j++) u[i][j] = mean;
	int t = 0; //tracks how many iterations can be processed before requiring a ghost cell update
	int start = 0;  //modified starting position for i
	int end = 0; //modified ending position for i
	for (k = 0; k < iterations; k++) {
		diff = 0.0;
		if (t >= boundary_thickness)
		{ 
			//Message passing
			if (rank != (p-1))
			{
				//Pass lower real cells to rank+1's upper ghost cells
				//Recieve lower ghost cells from rank+1's upper real cells
				MPI_Send(&my_num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(&other_num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
			}
			if (rank != 0)
			{
				//Recieve upper ghost cells from rank-1's lower real cells
				//Pass upper real cells to rank-1's lower ghost cells
				MPI_Recv(&other_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
				MPI_Send(&my_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);				
			}
			t = 0;
		}
		for (i = 1; i < num_rows-1; i++)
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

		for (i = 1; i < num_rows-1; i++)
			for (j=1; j < N-1; j++) u[i][j] = w[i][j];
		t++;
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

/*
int MPI_Send (
      void         *message,
      int           count,
      MPI_Datatype  datatype,
      int           dest,
      int           tag,
      MPI_Comm      comm
)
int MPI_Recv (
      void         *message,
      int           count,
      MPI_Datatype  datatype,
      int           source,
      int           tag,
      MPI_Comm      comm,
      MPI_Status   *status
)
*/