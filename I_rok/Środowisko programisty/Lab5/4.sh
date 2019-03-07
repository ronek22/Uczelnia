#!/bin/bash
echo "Z ilu chcesz policzyc silnie: "
read n
silnia=1

for(( i=1; $i<=n; i++ )) ; do
	silnia=$[silnia*i]
done

echo "Silnia ($n) = $silnia"
