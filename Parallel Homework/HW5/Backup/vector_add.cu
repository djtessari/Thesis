// This CUDA program implements vector addition on both the CPU & GPU
//
// To compile:
//  nvcc -O3 vector_add.cu -o vector_add
// Note: if /usr/local/cuda/bin is not in your $PATH, you will need to
//  specify the full path to nvcc: /usr/local/cuda/bin/nvcc
//
// To run:
//  ./vector_add N
//  (where N is the number of elements in each vector)


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Function declarations
float *CPU_add_vectors(float *A, float *B, int N);
float *GPU_add_vectors(float *A, float *B, int N);
float *get_random_vector(int N);
long long start_timer();
long long stop_timer(long long start_time, char *name);
void die(char *message);
void check_error(cudaError e);


// The number of threads per blocks in the kernel
// (if we define it here, then we can use its value in the kernel,
//  for example to statically declare an array in shared memory)
const int threads_per_block = 256;


int main(int argc, char **argv) {
	// Seed the random generator (use a constant here for repeatable results)
	srand(4444);

	// Determine the vector length
	int N = 100000;  // default value
	if (argc > 1) N = atoi(argv[1]); // user-specified value

	// Generate two random vectors
	long long vector_start_time = start_timer();
	float *A = get_random_vector(N);
	float *B = get_random_vector(N);
	stop_timer(vector_start_time, "Vector generation");
	
	// Compute their sum on the GPU
	long long GPU_start_time = start_timer();
	float *C_GPU = GPU_add_vectors(A, B, N);
	long long GPU_time = stop_timer(GPU_start_time, "\t            Total");
	
	// Compute their sum on the CPU
	long long CPU_start_time = start_timer();
	float *C_CPU = CPU_add_vectors(A, B, N);
	long long CPU_time = stop_timer(CPU_start_time, "\nCPU");
	
	// Compute the speedup or slowdown
	if (GPU_time > CPU_time) printf("\nCPU outperformed GPU by %.2fx\n", (float) GPU_time / (float) CPU_time);
	else                     printf("\nGPU outperformed CPU by %.2fx\n", (float) CPU_time / (float) GPU_time);
	
	// Check the correctness of the GPU results
	int num_wrong = 0;
	for (int i = 0; i < N; i++) {
		if (fabs(C_CPU[i] - C_GPU[i]) > 0.000001) num_wrong++;
	}
	
	// Report the correctness results
	if (num_wrong) printf("\n%d / %d values incorrect\n", num_wrong, N);
	else           printf("\nAll values correct\n");

}


// A GPU kernel that computes the vector sum A + B
// (each thread computes a single value of the result)
__global__ void add_vectors_kernel(float *A, float *B, float *C, int N) {
	// Determine which element this thread is computing
	// Note: here we need to convert from the two-dimensional grid of
	//  thread blocks back to a one-dimensional index into the arrays
	int block_id = blockIdx.x + gridDim.x * blockIdx.y;
	int thread_id = blockDim.x * block_id + threadIdx.x;
	
	// Make sure we do not go off the end of the array
	if (thread_id < N) {
		// Compute a single element of the result vector
		C[thread_id] = A[thread_id] + B[thread_id];
	}
}


// Returns the vector sum A + B (computed on the GPU)
float *GPU_add_vectors(float *A_CPU, float *B_CPU, int N) {
	
	long long memory_start_time = start_timer();

	// Allocate GPU memory for the inputs and the result
	int vector_size = N * sizeof(float);
	float *A_GPU, *B_GPU, *C_GPU;
	check_error(cudaMalloc((void **) &A_GPU, vector_size));
	check_error(cudaMalloc((void **) &B_GPU, vector_size));
	check_error(cudaMalloc((void **) &C_GPU, vector_size));
	
	// Transfer the input vectors to GPU memory
	check_error(cudaMemcpy(A_GPU, A_CPU, vector_size, cudaMemcpyHostToDevice));
	check_error(cudaMemcpy(B_GPU, B_CPU, vector_size, cudaMemcpyHostToDevice));
	
	stop_timer(memory_start_time, "\nGPU:\t  Transfer to GPU");
	
	// Determine the number of thread blocks in the x- and y-dimension
	// Note: we use a two-dimensional grid of thread blocks here because each dimension
	//  of the grid can only have up to 64K thread blocks; if we want to use more than
	//  64K thread blocks, we need to use a two-dimensional grid. This is slightly
	//  awkward, however, since the underlying problem is inherently one-dimensional
	int num_blocks = (N + threads_per_block - 1) / threads_per_block;
	int max_blocks_per_dimension = 65535;
	int num_blocks_y = (int) ((float) (num_blocks + max_blocks_per_dimension - 1) / (float) max_blocks_per_dimension);
	int num_blocks_x = (int) ((float) (num_blocks + num_blocks_y - 1) / (float) num_blocks_y);
	dim3 grid_size(num_blocks_x, num_blocks_y, 1);
	
	// Execute the kernel to compute the vector sum on the GPU
	long long kernel_start_time = start_timer();
	add_vectors_kernel <<< grid_size , threads_per_block >>> (A_GPU, B_GPU, C_GPU, N);
	cudaThreadSynchronize();  // This is only needed for timing and error-checking purposes
	stop_timer(kernel_start_time, "\t Kernel execution");
	
	// Check for kernel errors
	check_error(cudaGetLastError());
	
	// Allocate CPU memory for the result
	float *C_CPU = (float *) malloc(vector_size);
	if (C_CPU == NULL) die("Error allocating CPU memory");
	
	// Transfer the result from the GPU to the CPU
	memory_start_time = start_timer();
	check_error(cudaMemcpy(C_CPU, C_GPU, vector_size, cudaMemcpyDeviceToHost));
	stop_timer(memory_start_time, "\tTransfer from GPU");
	
	// Free the GPU memory
	check_error(cudaFree(A_GPU));
	check_error(cudaFree(B_GPU));
	check_error(cudaFree(C_GPU));
	
	return C_CPU;
}


// Returns the vector sum A + B
float *CPU_add_vectors(float *A, float *B, int N) {	
	// Allocate memory for the result
	float *C = (float *) malloc(N * sizeof(float));
	if (C == NULL) die("Error allocating CPU memory");

	// Compute the sum;
	for (int i = 0; i < N; i++) C[i] = A[i] + B[i];
	
	// Return the result
	return C;
}


// Returns a randomized vector containing N elements
float *get_random_vector(int N) {
	if (N < 1) die("Number of elements must be greater than zero");
	
	// Allocate memory for the vector
	float *V = (float *) malloc(N * sizeof(float));
	if (V == NULL) die("Error allocating CPU memory");
	
	// Populate the vector with random numbers
	for (int i = 0; i < N; i++) V[i] = (float) rand() / (float) rand();
	
	// Return the randomized vector
	return V;
}


// Returns the current time in microseconds
long long start_timer() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}


// Prints the time elapsed since the specified time
long long stop_timer(long long start_time, char *label) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long long end_time = tv.tv_sec * 1000000 + tv.tv_usec;
	printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000));
	return end_time - start_time;
}


// Prints the specified message and quits
void die(char *message) {
	printf("%s\n", message);
	exit(1);
}

// If the specified error code refers to a real error, report it and quit the program
void check_error(cudaError e) {
	if (e != cudaSuccess) {
		printf("\nCUDA error: %s\n", cudaGetErrorString(e));
		exit(1);
	}
}
