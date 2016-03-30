#!/bin/bash
for i in $( find ~ -iname "l*" -a -type d )
do
	echo $i
done
