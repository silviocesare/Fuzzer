#!/bin/bash

TEMPNAME=fuzz.tmp
for filename in $(cat $1); do
	echo "DOING $filename"
	names=""
	for i in $(seq 1 1000); do
		../MutationFuzzer -b 0.001 $filename > $TEMPNAME.$i
		names="$names $TEMPNAME.$i"
	done
	echo $names
	../DebugLaunch /usr/bin/clamscan clamscan $names
	if [ $? -eq 100 ]; then
		echo GOT A CRASH
		exit 1
	fi
done
