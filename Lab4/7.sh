#! /bin/bash

echo "Zmienne Srodowiskowe"
echo -e "Login:$USER\nHost:$HOSTNAME\nSciezka:$HOME" 
x=20
pol=`pwd`
szukaj=`find $pol -type f -a -iname '*.txt'`

echo -e "\nZmienne Programowe"
echo -e "Wartosc x = $x \nSciezka do obecnego katalogu: $pol \nSzukaj plikow txt: \n$szukaj"
