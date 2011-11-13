#!/bin/bash  	 
#$ -V 				# Inherit the submission environment
#$ -cwd 			# Start job in submission directory
#$ -j y 			# Combine stderr and stdout
#$ -N myJob			# Job Name
#$ -o $JOB_NAME.o$JOB_ID	# Name of the output file (eg. myMPI.oJobID)
#$ -pe 16way 16 		# Requests 16 tasks/node, 32 cores total
#$ -q normal	 		# Queue name "normal"
#$ -l h_rt=02:00:00 		# Run time (hh:mm:ss) - 2 hours
#$ -M n				# Use email notification address
#$ -m be 			# Email at Begin and End of joba

set -x 				# Echo commands, use "set echo" with cshdd

#Default MPI type is mvapich with PGI compiler

#uncomment the following to us mvapich2 with GNU compiler
#module unload mvapich
#module unload pgi
#module load gcc
#module load mvapich2

module list

ibrun halo 1 100 1		# Run the MPI executable
