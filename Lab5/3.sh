#!/bin/bash
echo "Podaj n: "
read n
i=2
suma=0

while [ $i -le $n ] ; do
	suma=$[suma+i]
	i=$[i+2]
done

echo "Suma = $suma"
