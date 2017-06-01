#!/bin/bash
echo "Podaj nr miesiaca: "
read month

if (($month >=1)) && (($month <=3)) ; then
	echo "Zima"
elif (($month >=4)) && (($month <=6)) ; then
	echo "Wiosna"
elif (($month >=7)) && (($month <=9)) ; then
	echo "Lato"
elif (($month >=10)) && (($month <=12)) ; then
	echo "Jesien"
else
	echo "Nie wprowadzono miesiace"
fi

