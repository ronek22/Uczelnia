#!/bin/bash

#skrypt pobiera 2 parametry, plik i liczbe
#zarezerwowane bledy 1-2 126-165 255

bledna_liczba_param=10
plik_nie_istnieje=11
zmienna_nie_jest_liczba=12

if [ $# -ne 2 ]
then
	echo "Bledna liczba parametrow."
	exit $bledna_liczba_param
fi

if ! [ -a "$1" ]
then
	echo "Plik $1 nie istnieje w $PWD"
	exit $plik_nie_istnieje
fi

if ! [[ $2 =~ ^-?[0-9]+$ ]]
then
	echo "$2 nie jest liczba calkowita"
	exit $zmienna_nie_jest_liczba
fi

echo "Podales plik $1 i liczbe calkowita $2"
exit 0

