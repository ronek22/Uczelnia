#!/bin/bash
echo "Wprowadz liczby[po spacji]"
read a b
echo "Dane sa liczby a=$a, b=$b"
PS3='Co wybierasz? '
select y in "mnozenie" "dodawanie" "odejmowanie" "quit"
do
	case $y in
		"mnozenie") echo "$a*$b=$[a*b]" ;;
		"dodawanie") echo "$a+$b=$[a+b]" ;;
		"odejmowanie") echo "$a-$b=$[a-b]" ;;
		"quit") break ;;
		*) echo "Cos zle wybrales"
	esac
done
