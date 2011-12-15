#!/bin/bash
#
# This is a sample script that will create 8 other jobs (that really
# don't do much), and send them through qsub

NODES=1

if [ "$PBS_ENVIRONMENT" != "" ] ; then
    echo Ack!  Launched via a qsub -- not continuing
    exit
fi
# 1, 2, 5, 10, 25 nodes
for (( i = 1; i <= $NODES; i++ )); do	
    echo "Creating job for node $i..."
    echo "#!/bin/bash" > myjob-$NODES\-$i.pbs
    echo "#PBS -q generals -l cuda_gpu=1" >> myjob-$NODES\-$i.pbs
	echo "#PBS -m ea" >> myjob-$NODES\-$i.pbs
	echo "#PBS -M djt2a@virginia.edu" >> myjob-$NODES\-$i.pbs
	echo "cd \$PBS_O_WORKDIR" >> myjob-$NODES\-$i.pbs
	echo "hostname" >> myjob-$NODES\-$i.pbs
    echo "./plate_cuda 100 100 100" >> myjob-$NODES\-$i.pbs
    qsub myjob-$NODES\-$i.pbs
    /bin/rm -f myjob-$NODES\-$i.pbs
done