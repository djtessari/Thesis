/* Sections of code have been removed to more clearly show 
	the changes made to make the NUMA version of the program.
	*/

// Threaded function
void *LoopPlate(void *threadarg){
	struct thread_data *data;
	
	/*...*/
	
	int my_node;
	my_node = ceil( num_threads / 8 ); 
	numa_run_on_node(my_node);	
	
	/*...*/
	
	for (i = 0; i < iterations; i++) { /*...*/}
	
	/*...*/
	
	pthread_exit((void*) threadarg);
	

}


int main(int argc, char **argv) {
	// Record the start time of the program
	time_t start_time = time(NULL);
	/*...*/
	
	
	// Determine if NUMA is enabled on the system, required for NUMA functions
	if (numa_available() < 0) {
		printf("NUMA not available");
		
	}
	else{
	
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
	
	/*...*/
	
	return 0;
	}
	
	/*...*/

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
/*..*/