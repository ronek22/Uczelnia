#!/bin/bash

F=(0 1)

echo -e "Ciag Fibbonaciego\nPodaj n: "
read n

echo "0: ${F[0]}"
echo "1: ${F[1]}"
for((i=2;$i<n;i++)) ; do
	F[i]=$[F[i-1]+F[i-2]]
	echo "$i: ${F[i]}"
done

