#!/bin/bash
#
# This is a sample script that will create 8 other jobs (that really
# don't do much), and send them through qsub

NODES=5

if [ "$PBS_ENVIRONMENT" != "" ] ; then
    echo Ack!  Launched via a qsub -- not continuing
    exit
fi
# 1, 2, 5, 10, 25 nodes
for (( i = 1; i <= $NODES; i++ )); do

	let ratio=250/$NODES
	let sta=$i-1
	let sta*=ratio
	let sta=$sta+1
	
	let en=$i
	let en*=ratio
	
    echo "Creating job for node $i..."
    echo "#!/bin/bash" > myjob-$NODES\-$i.pbs
    echo "#PBS -l nodes=1" >> myjob-$NODES\-$i.pbs
    echo "#PBS -l walltime=0:40:00" >> myjob-$NODES\-$i.pbs
	echo "#PBS -m ea" >> myjob-$NODES\-$i.pbs
	echo "#PBS -M djt2a@virginia.edu" >> myjob-$NODES\-$i.pbs
	echo "cd \$PBS_O_WORKDIR" >> myjob-$NODES\-$i.pbs
    echo "/usr/bin/blender -b Star-collapse-ntsc.blend -s $sta -e $en -a" >> myjob-$NODES\-$i.pbs
    qsub myjob-$NODES\-$i.pbs
    /bin/rm -f myjob-$NODES\-$i.pbs
done


#
# note that there is another format for for loops in bash:
#
# for i in cheese apple crackers
# do
#   echo $i
# done

