#!/bin/sh
CORE=3
if [ -n "$1" ] ; then
TH=$1
else
TH=10
fi
echo CORE=$CORE
echo TH=$TH

while killall test-host ; do : ;done
cnt=0; while : ; do echo cnt=$cnt; cnt=$(($cnt+1));
        taskset -c $CORE ./test-host&
        taskset -c 0  dstat -C $CORE -c 1 10 | tee /tmp/test
	AVG=$(sed /tmp/test -e '1,3d' | awk '{sum+=$2}END{printf "%d",sum/NR}')
	echo AVG=$AVG
	if [ "$AVG" -ge $TH ] ; then
		echo high cpu sys usage....
		break;
	else
		while killall test-host ; do : ;done
	fi
done
taskset -c 0  dstat -C $CORE -c

