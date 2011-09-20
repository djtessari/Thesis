#!/bin/bash
#
# This is a sample script that will create 8 other jobs (that really
# don't do much), and send them through qsub

NODES=1

if [ "$PBS_ENVIRONMENT" != "" ] ; then
    echo Ack!  Launched via a qsub -- not continuing
    exit
fi

for (( i = 1; i <= $NODES; i++ )); do
    echo "Creating job for node $i..."
    echo "#!/bin/bash" > job-$i.pbs
    echo "#PBS -l nodes=1" >> job-$i.pbs
    echo "#PBS -l walltime=0:05:00" >> job-$i.pbs
	echo "Output" > output-$i.pbs
	echo "#PBS -o output-$i" >> job-$i.pbs
	echo "#PBS -j oe" >> job-$i.pbs
	echo "#PBS -m ea" >> job-$i.pbs
	echo "#PBS -M djt2a@virginia.edu" >> job-$i.pbs
	echo "cd \$PBS_O_WORKDIR" >> job-$i.pbs
    echo "/usr/bin/blender -b Star-collapse-ntsc.blend -s 1 -e 5 -a" >> job-$i.pbs
    qsub job-$i.pbs
    /bin/rm -f job-$i.pbs
done


#
# note that there is another format for for loops in bash:
#
# for i in cheese apple crackers
# do
#   echo $i
# done

