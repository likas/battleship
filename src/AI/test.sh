#!/bin/bash

echo "Press [CTRL+C] to stop.."
sum=0
count=0
while :
do
	let sum+=$($1)
	let count++
	echo $(echo "$sum/$count" | bc -l)
	sleep 1
done
