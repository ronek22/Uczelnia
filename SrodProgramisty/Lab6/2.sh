#!/bin/bash
echo "Wprowadz a: "
read a
echo "Wprowadz b: "
read b

if test $a = $b #zastosowanie slowa test
then 
	echo "$a jest rowne $b"
elif [ $a -gt $b ] #zastosowanie []
then
	echo "$a jest wieksze niz $b"
else
	echo "$a jest mniejsze niz $b"
fi

