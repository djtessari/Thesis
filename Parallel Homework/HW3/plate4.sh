#!/bin/csh
#PBS -l ncpus=16
#ncpus must be a multiple of 16
#PBS -l walltime=60:00              
#PBS -j oe
#PBS -q batch

ja 

COLS=10000
ROWS=10000
ITR=10000
THREADS=4


#move to my $SCRATCH directory
cd $SCRATCH

#copy executable to $SCRATCH
cp $HOME/a .

#run my executable
setenv OMP_NUM_THREADS $THREADS
omplace -nt $OMP_NUM_THREADS ./a $COLS $ROWS $ITR $THREADS

ja -chlst
