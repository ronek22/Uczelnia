#!/bin/bash
PS3='Wybierz ulubiony kolor: ' #domyslny tekst
lista=("bialy" "czerwony" "czarny" "niebieski")

select color in ${lista[*]}
do
	if [ ${#lista[*]} -ge $REPLY ] ; then
		echo
		echo "Twoj ulubiony kolor to $color"
	else
		echo "Numerek sie nie zgadza!"
	fi
break # bez break'a program sie nie zakonczy
done
exit
