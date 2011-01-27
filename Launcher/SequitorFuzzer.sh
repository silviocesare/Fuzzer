#!/bin/bash

TEMPNAME=fuzz.tmp
for filename in $(cat $1); do
	echo "DOING $filename"
	names=""
	for i in $(seq 1 100); do
		cat $filename | ../Sequitor|../SequitorFuzzer|../SequitorOutput > $TEMPNAME.$i
		names="$names $TEMPNAME.$i"
	done
	echo $names
#	../DebugLaunch /usr/bin/clamscan clamscan $names
	for i in $names; do
		sudo /home/silvio/MalwareDetectorClient -t 0 -h 192.168.1.50 $i
	done
	if [ $? -eq 100 ]; then
		echo GOT A CRASH
		exit 1
	fi
done
