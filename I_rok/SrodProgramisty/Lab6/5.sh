#!/bin/bash

#1
echo -e "1:\n"
for i in `seq 10`
do
	echo "$i"
done

echo -e "\n2:\n"

#2
for i in `seq 0 2 10`
do
	echo $i
done

echo -e "\n3:\n"

#3
for i in {1..10}
do
	echo $i
done

echo -e  "\n4:\n"

#4
for ((i = 1; i <= 10; i++))
do
	echo $i
done
