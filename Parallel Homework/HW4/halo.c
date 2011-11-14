// This program simulates the flow of heat through a two-dimensional plate.
// The number of grid cells used to model the plate as well as the number of
//  iterations to simulate can be specified on the command-line as follows:
//  ./heated_plate_sequential <columns> <rows> <iterations>
// For example, to execute with a 500 x 500 grid for 250 iterations, use:
//  ./heated_plate_sequential 500 500 250


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>


// Define the immutable boundary conditions and the inital cell value
#define TOP_BOUNDARY_VALUE 0.0
#define BOTTOM_BOUNDARY_VALUE 100.0
#define LEFT_BOUNDARY_VALUE 0.0
#define RIGHT_BOUNDARY_VALUE 100.0
#define INITIAL_CELL_VALUE 50.0


// Function prototypes
void print_cells(float **cells, int n_x, int n_y);
void initialize_cells(float **cells, int n_x, int n_y);
void create_snapshot(float **cells, int n_x, int n_y, int id);
float **allocate_cells(int n_x, int n_y);
void die(const char *error);


int main(int argc, char **argv) {
	// Record the start time of the program
	time_t start_time = time(NULL);

	int iters = 0;
	int k = 0;
	int elapsedTime;
	int rank, p;
	// Initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsedTime = -MPI_Wtime();
	// Get the rank of the curren process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Get the total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	//Number of inner loop iterations.  Put loop around next[i,j]=(old[i-1,j...)*.25;
	int iters_per_cell = (argc > 1) ? atoi(argv[1]) : 1;
	//Number of iterations, same as before
	int iterations = (argc > 2) ? atoi(argv[2]) : 100;
	//How many ghost cell layers to send at a time & how many internal iterations to perform
	//per communication
	int boundary_thickness = (argc > 3) ? atoi(argv[3]) : 1;
	//Note: Ghost Cells are memory locations used to store redundant copies of 
	//data held by neighboring processes
	
	// Extract the input parameters from the command line arguments
	// Number of columns in the grid (default = 1,000)
	int num_cols = 160;
	// Number of rows in the grid (default = 1,000)
	int total_num_rows = 160;
	// Number of iterations to simulate (default = 100)
	//int iterations = 100;
	int num_rows = (total_num_rows / p);
	
	// Output the simulation parameters
	//printf("Grid: %dx%d, Iterations: %d\n", num_cols, num_rows, iterations);
		
	// We allocate two arrays: one for the current time step and one for the next time step.
	// At the end of each iteration, we switch the arrays in order to avoid copying.
	// The arrays are allocated with an extra surrounding layer which contains
	//  the immutable boundary conditions (this simplifies the logic in the inner loop).
	
	int added_boundary = 0;
	if (rank != 0) added_boundary+=boundary_thickness;
	if (rank != (p-1)) added_boundary+=boundary_thickness;
	num_rows += added_boundary;

	float **cells[2];
	cells[0] = allocate_cells(num_cols + 2, num_rows + 2);
	cells[1] = allocate_cells(num_cols + 2, num_rows + 2);
	int cur_cells_index = 0, next_cells_index = 1;
	
	// Initialize the interior (non-boundary) cells to their initial value.
	// Note that we only need to initialize the array for the current time
	//  step, since we will write to the array for the next time step
	//  during the first iteration.
	initialize_cells(cells[0], num_cols, num_rows);
	
	// Set the immutable boundary conditions in both copies of the array
	int x, y, i;
	if (rank == 0) for (x = 1; x <= num_cols; x++) cells[0][0][x] = cells[1][0][x] = TOP_BOUNDARY_VALUE;
	if (rank == (p-1)) for (x = 1; x <= num_cols; x++) cells[0][num_rows + 1][x] = cells[1][num_rows + 1][x] = BOTTOM_BOUNDARY_VALUE;
	for (y = 1; y <= num_rows; y++) cells[0][y][0] = cells[1][y][0] = LEFT_BOUNDARY_VALUE;
	for (y = 1; y <= num_rows; y++) cells[0][y][num_cols + 1] = cells[1][y][num_cols + 1] = RIGHT_BOUNDARY_VALUE;
	MPI_Status status;
	int t = 0;
	// Simulate the heat flow for the specified number of iterations
	for (i = 0; i < iterations; i++) {
		// Traverse the plate, computing the new value of each cell

		if (t >= boundary_thickness)
		{ 
			int count = (boundary_thickness * num_cols);
			//Message passing
			if (rank != (p-1))
			{
				//Pass lower real cells to rank+1's upper ghost cells
				//Recieve lower ghost cells from rank+1's upper real cells

				float lowerCells[boundary_thickness][num_cols];
				int r, c = 0;
				for (r = 0; r < boundary_thickness; r++){
					for (c = 0; c < num_cols; c++){
						lowerCells[r][c] = cells[cur_cells_index][num_rows-boundary_thickness-1+r][c+1];
					}
				}

				MPI_Send(&lowerCells, count, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD);
				MPI_Recv(&lowerCells, count, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD, &status);

				for (r = 0; r < boundary_thickness; r++){
					for (c = 0; c < num_cols; c++){
						cells[cur_cells_index][num_rows-boundary_thickness-1+r][c+1] = lowerCells[r][c];
					}
				}

			}
			if (rank != 0)
			{
				//Recieve upper ghost cells from rank-1's lower real cells
				//Pass upper real cells to rank-1's lower ghost cells
				float upperCells[boundary_thickness][num_cols];
				int r, c = 0;
				for (r = 0; r < boundary_thickness; r++){
					for (c = 0; c < num_cols; c++){
						upperCells[r][c] = cells[cur_cells_index][r+1][c+1];
					}
				}	

				MPI_Recv(&upperCells, count, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD, &status);
				MPI_Send(&upperCells, count, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD);	

				for (r = 0; r < boundary_thickness; r++){
					for (c = 0; c < num_cols; c++){
						cells[cur_cells_index][r+1][c+1] = upperCells[r][c];
					}
				}
			}
			t = 0;
		}
		for (y = 1; y <= num_rows; y++) {
			for (x = 1; x <= num_cols; x++) {
				int k = 0;
				for (k=0; k < iters_per_cell; k++){
				// The new value of this cell is the average of the old values of this cell's four neighbors
					cells[next_cells_index][y][x] = (cells[cur_cells_index][y][x - 1]  +
													 cells[cur_cells_index][y][x + 1]  +
													 cells[cur_cells_index][y - 1][x]  +
													 cells[cur_cells_index][y + 1][x]) * 0.25;
				}
			}
		}
		
		// Swap the two arrays
		cur_cells_index = next_cells_index;
		next_cells_index = !cur_cells_index;
		t++;
		
		// Print the current progress
		//printf("Iteration: %d / %d\n", i + 1, iterations);
	}
	
	// Output a snapshot of the final state of the plate
	int final_cells = (iterations % 2 == 0) ? 0 : 1;
	//create_snapshot(cells[final_cells], num_cols, num_rows, iterations);

	// Compute and output the execution time
	time_t end_time = time(NULL);
	printf("\nExecution time: %d seconds\n", (int) difftime(end_time, start_time));

	//End process prints out the full array
	if (rank == 0)
	{
		printf("\nRank 0 Gathering Cells\n");
		float **allCells;
		allCells = allocate_cells(num_cols + 2, total_num_rows + 2);
		int i,j = 0;
		for (i = 0; i < (total_num_rows + 2); i++)
		{
			if (i < (num_rows - added_boundary + 2))
			{
				for (j = 0; j < (num_cols + 2); j++)
				{
					allCells[i][j] = cells[final_cells][i][j];
				}
			}
			else
			{
				int target;
				target = (i / (num_rows - added_boundary));
				float **tempCells;
				int count = ((num_rows - boundary_thickness+2) * num_cols);
				printf("\nCount = %i", count);
				printf("\nRank 0 Wait On Rank %i\n", target);
				MPI_Recv(&tempCells, count, MPI_FLOAT, target, 0, MPI_COMM_WORLD, &status);		
				int k;
				for (k = 0; k < count; k++)
				{
					for (j = 0; j < num_cols; j++)
					{
						allCells[i][j] = tempCells[k][j];
					}
				}			
			}
		}
		create_snapshot(allCells, num_cols, total_num_rows, iterations);
	}
	else
	{
		float **returnCells;
		returnCells = allocate_cells(num_cols, (num_rows - added_boundary));
		int i,j = 0;
		
		for (i = 0; i < (num_rows - added_boundary); i++)
		{
			for (j = 0; j < num_cols; j++)
			{
				returnCells[i][j] = cells[final_cells][i+added_boundary][j];
			}
		}
		
		int count = ((num_rows - added_boundary) * num_cols);
		printf("\nCount = %i", count);
		printf("\nRank %i Send To Rank 0\n", rank);
		MPI_Send(&returnCells, count, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	elapsedTime+=MPI_Wtime();
	if (rank==0)
	{
		printf("\nElapsed time: %d seconds\n", (int) elapsedTime);
	}

	
	MPI_Finalize();
	
	return 0;
}


// Allocates and returns a pointer to a 2D array of floats
float **allocate_cells(int num_cols, int num_rows) {
	float **array = (float **) malloc(num_rows * sizeof(float *));
	if (array == NULL) die("Error allocating array!\n");
	
	array[0] = (float *) malloc(num_rows * num_cols * sizeof(float));
	if (array[0] == NULL) die("Error allocating array!\n");

	int i;
	for (i = 1; i < num_rows; i++) {
		array[i] = array[0] + (i * num_cols);
	}

	return array;
}


// Sets all of the specified cells to their initial value.
// Assumes the existence of a one-cell thick boundary layer.
void initialize_cells(float **cells, int num_cols, int num_rows) {
	int x, y;
	for (y = 0; y <= num_rows+1; y++) {
		for (x = 0; x <= num_cols+1; x++) {
			cells[y][x] = INITIAL_CELL_VALUE;
		}
	}
}


// Creates a snapshot of the current state of the cells in PPM format.
// The plate is scaled down so the image is at most 1,000 x 1,000 pixels.
// This function assumes the existence of a boundary layer, which is not
//  included in the snapshot (i.e., it assumes that valid array indices
//  are [1..num_rows][1..num_cols]).
void create_snapshot(float **cells, int num_cols, int num_rows, int id) {
	int scale_x, scale_y;
	scale_x = scale_y = 1;
	
	// Figure out if we need to scale down the snapshot (to 1,000 x 1,000)
	//  and, if so, how much to scale down
	if (num_cols > 1000) {
		if ((num_cols % 1000) == 0) scale_x = num_cols / 1000;
		else {
			die("Cannot create snapshot for x-dimensions >1,000 that are not multiples of 1,000!\n");
			return;
		}
	}
	if (num_rows > 1000) {
		if ((num_rows % 1000) == 0) scale_y = num_rows / 1000;
		else {
			printf("Cannot create snapshot for y-dimensions >1,000 that are not multiples of 1,000!\n");
			return;
		}
	}
	
	// Open/create the file
	char text[255];
	sprintf(text, "snapshot.%d.ppm", id);
	FILE *out = fopen(text, "w");
	// Make sure the file was created
	if (out == NULL) {
		printf("Error creating snapshot file!\n");
		return;
	}
	
	// Write header information to file
	// P3 = RGB values in decimal (P6 = RGB values in binary)
	fprintf(out, "P3 %d %d 100\n", num_rows / scale_y, num_cols / scale_x);
	
	// Precompute the value needed to scale down the cells
	float inverse_cells_per_pixel = 1.0 / ((float) scale_x * scale_y);
	
	// Write the values of the cells to the file
	int x, y, i, j;
	for (y = 1; y <= num_rows; y += scale_y) {
		for (x = 1; x <= num_cols; x += scale_x) {
			float sum = 0.0;
			for (j = y; j < y + scale_y; j++) {
				for (i = x; i < x + scale_x; i++) {
					sum += cells[j][i];
				}
			}
			// Write out the average value of the cells we just visited
			int average = (int) (sum * inverse_cells_per_pixel);
			fprintf(out, "%d 0 %d\t", average, 100 - average);
		}
		fwrite("\n", sizeof(char), 1, out);
	}
	
	// Close the file
	fclose(out);
}


// Prints the specified error message and then exits
void die(const char *error) {
	printf("%s", error);
	exit(1);
}
