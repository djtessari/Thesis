// This program simulates the flow of heat through a two-dimensional plate.
// The number of grid cells used to model the plate as well as the number of
//  iterations to simulate can be specified on the command-line as follows:
//  ./heated_plate_sequential <columns> <rows> <iterations>
// For example, to execute with a 500 x 500 grid for 250 iterations, use:
//  ./heated_plate_sequential 500 500 250

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <numa.h>
#include <math.h>


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
float **allocate_numa_cells(int n_x, int n_y, int n_z);
void die(const char *error);

//typedef float **Array[2];

// Struct to pass information to threads
struct thread_data{
	int thread_id;
	int num_threads;
	int num_rows;
	int num_cols;
	int iterations;
	//float **cells0;
	//float **cells1;
};

pthread_mutex_t thresh_mutex;
pthread_mutex_t sem_mutex;
pthread_cond_t threshold;
pthread_attr_t attr;
sem_t waiting;
sem_t done;

float **cells[2];
int isdone;

// Threaded function
void *LoopPlate(void *threadarg){
	struct thread_data *data;
	data = (struct thread_data *) threadarg;
	int id = data->thread_id;
	int num_threads = data->num_threads;
	int num_rows = data->num_rows;
	int num_cols = data->num_cols;
	int iterations = data->iterations;
	int cur_cells_index = 0;
	int next_cells_index = 1;
	
	//Set this thread to run on its designated node
	int my_node;
	my_node = ceil( num_threads / 8 ); 

	numa_run_on_node(my_node);

	//float **cells0 = data->cells0;
	//float **cells1 = data->cells1;
	int x,y,i,j;
	int sem_val1, sem_val2;
	int y_start;
	double multi;
	int y_end;
	multi = (double) num_rows;
	multi = multi / num_threads;
	y_start = (((id-1) * multi) + 1);
	y_end = ((id * multi));
	
	
	for (i = 0; i < iterations; i++) {

		//printf("cell value = %f\n", cells[cur_cells_index][x][y]);
				

		for (y = y_start; y <= y_end; y++) {
			for (x = 1; x <= num_cols; x++) {

				// The new value of this cell is the average of the old values of this cell's four neighbors
				
				cells[next_cells_index][y][x] = (cells[cur_cells_index][y][x - 1]  +
													cells[cur_cells_index][y][x + 1]  +
													cells[cur_cells_index][y - 1][x]  +
													cells[cur_cells_index][y + 1][x]) * 0.25;
				/*if (cur_cells_index == 0){
				
					cells1[y][x] = (cells0[y][x - 1]  +
										cells0[y][x + 1]  +
										cells0[y - 1][x]  +
										cells0[y + 1][x]) * 0.25;
				}
				else{
				
					cells0[y][x] = (cells1[y][x - 1]  +
										cells1[y][x + 1]  +
										cells1[y - 1][x]  +
										cells1[y + 1][x]) * 0.25;
				}
				/**/
				//printf("cell value = %f\n", cells[cur_cells_index][x][y]);
			}
		}

		pthread_mutex_lock(&thresh_mutex);
		pthread_mutex_lock(&sem_mutex);

		sem_post(&done);
		sem_getvalue(&done, &sem_val1);
		sem_getvalue(&waiting, &sem_val2);

		if ((sem_val1 + sem_val2) == num_threads)
		{
			//printf("Thread %i is Unlocking threads\n", id);
			for (j=0; j < num_threads; j++){
				sem_wait(&done);
			}
			pthread_cond_broadcast(&threshold);
			pthread_mutex_unlock(&sem_mutex);
				
		}
		else
		{			
			//printf("Thread %i finished loop. Done = %i\n", id, sem_val1);
			pthread_mutex_unlock(&sem_mutex);
			pthread_cond_wait(&threshold, &thresh_mutex);
		}		
		pthread_mutex_unlock(&thresh_mutex);
		//sem_wait(&done);
		cur_cells_index = next_cells_index;
		next_cells_index = !cur_cells_index;
	}
	//sem_post(&waiting);
	printf("Exit loop, closing thread %i\n", id);
	
	//isdone = 1;
	pthread_exit((void*) threadarg);
	

}


int main(int argc, char **argv) {
	// Record the start time of the program
	time_t start_time = time(NULL);
	isdone = 0;
	
	// Extract the input parameters from the command line arguments
	// Number of columns in the grid (default = 1,000)
	int num_cols = (argc > 1) ? atoi(argv[1]) : 1000;
	// Number of rows in the grid (default = 1,000)
	int num_rows = (argc > 2) ? atoi(argv[2]) : 1000;
	// Number of iterations to simulate (default = 100)
	int iterations = (argc > 3) ? atoi(argv[3]) : 100;
	// Number of threads to use (default = 1)
	int num_threads = (argc > 4) ? atoi(argv[4]) : 1;
	
	// Output the simulation parameters
	printf("Grid: %dx%d, Iterations: %d\n", num_cols, num_rows, iterations);
		
	// We allocate two arrays: one for the current time step and one for the next time step.
	// At the end of each iteration, we switch the arrays in order to avoid copying.
	// The arrays are allocated with an extra surrounding layer which contains
	//  the immutable boundary conditions (this simplifies the logic in the inner loop).
	
	
	// Determine if NUMA is enabled on the system, required for NUMA functions
	if (numa_available() < 0) {
		printf("NUMA not available");
		/* Copy-paste non-numa code here */
	}
	else{
	
	
	
	//Its important to note that a Blacklight node consists of a socket
	//with 8 CPU cores each, and have their own physical memory.
	//Thus, every 8 threads can share a memory space without additional overhead
	/*
	a node is a set of CPUs (Central Processing Unit) that
	all have equal fast access to some memory using a memory controller.
	*/
	int max_node = numa_max_node();
	int nodes;
    nodes = ceil(((double)num_threads) / 8);  // 8 / 8 = 1 node, 16 / 8 = 2 nodes, ect.

	
	/* 	Now we figure out what range of cells each node will have access to.
		We will divide up evenly by rows
	*/
	
	//Sets the nodemasks and assigns memory to the appropriate node where it will be most used.
	int n;
	double multi;
	multi = num_rows+2;
	multi = multi / nodes;
	for (n = 1; n <= nodes; n++)
	{
			/* 	
				Now we figure out what range of cells each node will be assigned.
				We will divide up evenly by rows and assign memory to the node
				Its important to account for the border case cells as well, 1 extra row
				and column along each border.				
			*/
			
			int start_row = ((n-1) * ceil(multi));
			int end_row = (n * floor(multi));
			
			cells[0] = allocate_numa_cells(num_cols + 2, num_rows + 2, n);
			cells[1] = allocate_numa_cells(num_cols + 2, num_rows + 2, n);
			
		
	}
	
	/* Don't need this allocation anymore.
	
	//float **cells[2];
	cells[0] = allocate_cells(num_cols + 2, num_rows + 2);
	cells[1] = allocate_cells(num_cols + 2, num_rows + 2);*/
	
	int cur_cells_index = 0, next_cells_index = 1;

	
	// Initialize the interior (non-boundary) cells to their initial value.
	// Note that we only need to initialize the array for the current time
	//  step, since we will write to the array for the next time step
	//  during the first iteration.
	initialize_cells(cells[0], num_cols, num_rows);
	
	// Set the immutable boundary conditions in both copies of the array
	int x, y, i, t;
	for (x = 1; x <= num_cols; x++) cells[0][0][x] = cells[1][0][x] = TOP_BOUNDARY_VALUE;
	for (x = 1; x <= num_cols; x++) cells[0][num_rows + 1][x] = cells[1][num_rows + 1][x] = BOTTOM_BOUNDARY_VALUE;
	for (y = 1; y <= num_rows; y++) cells[0][y][0] = cells[1][y][0] = LEFT_BOUNDARY_VALUE;
	for (y = 1; y <= num_rows; y++) cells[0][y][num_cols + 1] = cells[1][y][num_cols + 1] = RIGHT_BOUNDARY_VALUE;
	
	// Create arrays for holding threads and args
	pthread_t threads[num_threads];
	struct thread_data thread_data_array[num_threads];
	
	pthread_mutex_init(&thresh_mutex, NULL);
	pthread_mutex_init(&sem_mutex, NULL);
	pthread_cond_init(&threshold, NULL);
	sem_init(&waiting, 0, 0);
	sem_init(&done, 0, 0);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	// Simulate the heat flow for the specified number of iterations
	//for (i = 0; i < iterations; i++) {
		//Start of thread based loops

	for (t=1; t <= num_threads; t++){
		thread_data_array[t].thread_id = t;
		thread_data_array[t].num_threads = num_threads;
		thread_data_array[t].num_rows = num_rows;
		thread_data_array[t].num_cols = num_cols;
						
		/*thread_data_array[t].cells0 = cells[0];
		thread_data_array[t].cells1 = cells[1];/*
		thread_data_array[t].cells = &cells;
		thread_data_array[t].cells = &cells[0];		
		thread_data_array[t].cells = *cells[0][0];		
		thread_data_array[t].cells = *cells;
		thread_data_array[t].cells = cells[0];		
		thread_data_array[t].cells = &cells[0][0];		
		thread_data_array[t].cells = **cells;
		thread_data_array[t].cells = *cells[0];
		thread_data_array[t].cells = cells[0][0];/**/

		thread_data_array[t].iterations = iterations;

		printf("Creating thread, id = %i\n", t);
		pthread_create(&threads[t], &attr, LoopPlate, (void *) &thread_data_array[t]);
	}

			/*
			// Traverse the plate, computing the new value of each cell
			for (y = 1; y <= num_rows; y++) {
				for (x = 1; x <= num_cols; x++) {
					// The new value of this cell is the average of the old values of this cell's four neighbors
					cells[next_cells_index][y][x] = (cells[cur_cells_index][y][x - 1]  +
													 cells[cur_cells_index][y][x + 1]  +
													 cells[cur_cells_index][y - 1][x]  +
													 cells[cur_cells_index][y + 1][x]) * 0.25;
				}
			}*/

		//End of thread based loops
		
		// Swap the two arrays
		/*
		cur_cells_index = next_cells_index;
		next_cells_index = !cur_cells_index;
		
		// Print the current progress
		printf("Iteration: %d / %d\n", i + 1, iterations);
	}*/
	void *status;
	pthread_attr_destroy(&attr);
	for (i = 1; i <= num_threads; i++){
		int rc = pthread_join(threads[i], &status);
	}
	// Output a snapshot of the final state of the plate
	
	int final_cells = (iterations % 2 == 0) ? 0 : 1;
	create_snapshot(cells[final_cells], num_cols, num_rows, iterations);

	// Compute and output the execution time
	time_t end_time = time(NULL);
	printf("\nExecution time: %d seconds\n", (int) difftime(end_time, start_time));

	
	//Free up the memory
	numa_free(cells, (((num_cols+2) * (num_rows+2) * sizeof(float)) + ((num_rows+2) * sizeof(float *))));
	
	pthread_mutex_destroy(&thresh_mutex);
	pthread_mutex_destroy(&sem_mutex);
	pthread_cond_destroy(&threshold);
	sem_destroy(&waiting);
	sem_destroy(&done);
	pthread_exit(NULL);
	}
	
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

// Allocates and returns a pointer to a 2D array of floats - NUMA version
float **allocate_numa_cells(int num_cols, int num_rows, int node) {
	float **array = (float **) numa_alloc_onnode(num_rows * sizeof(float *), node);
	if (array == NULL) die("Error allocating array!\n");
	
	array[0] = (float *) numa_alloc_onnode(num_rows * num_cols * sizeof(float), node);
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
	for (y = 1; y <= num_rows; y++) {
		for (x = 1; x <= num_cols; x++) {
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
