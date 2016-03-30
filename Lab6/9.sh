#!/bin/bash

var=0
LIMIT=10
while [ "$var" -lt "$LIMIT" ]
do
	echo "$var"
	var=`expr $var + 1` # inny sposob na obliczenia wyrazen arytmetycznych
done

END_CONDITION=end
until [ "$var1" = "$END_CONDITION" ]
do
	echo "Podaj wartosc zmiennej: "
	echo "($END_CONDITION to exit)"
	read var1
	echo "wczytales zmienna = $var1"
done
