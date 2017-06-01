#!/bin/bash

#lancuchowe
echo "Petla"
for i in "pon" "wt" "sr" "cz"
do
	echo $i
done

#2 sposob
echo -e "\nLista: "
lista="pon wt sr cz"
for i in $lista
do
	echo $i
done

#3 sposob
echo -e "\nTablica: "
tablica=(pon wt sr cz)
for i in ${tablica[@]}
do
	echo $i
done

echo -e "\nZlozone: "
for i in "pon 2" "wt 3" "sr 4"
do
	set -- $i
	echo "$1 to $2 dzien tygodnia"
done
