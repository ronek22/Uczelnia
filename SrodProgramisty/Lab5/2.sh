#!/bin/bash
echo "Podaj x: "
read x
echo "Podaj y: "
read y

if [ $y -ne 0 ] ; then
	echo "Wynik x/y = $[x/y]"
else
	echo "Nie mozna dzielic przez zero"
fi 
