#!/bin/bash
for (( i=1; i<=100; i++ )) 
do
	(time ./run.sh) 2>> $1
done
