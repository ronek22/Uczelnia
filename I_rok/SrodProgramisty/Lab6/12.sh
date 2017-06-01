#!/bin/bash
LIMIT=19
echo "Wypisuje liczby od 1 do 20(ale bez 3 i 11)."
a=0

while [ $a -le "$LIMIT" ]
do
	a=$(($a+1))
	if [ "$a" -eq 3 ] || [ "$a" -eq 11 ] ; then
		continue #omijamy reszte zawartosci petli
	fi
	echo "$a "
done
