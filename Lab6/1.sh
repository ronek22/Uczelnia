#!/bin/bash
echo "Podaj napis"
read napis
echo ${#napis} #dlugosc ciagu
echo ${napis:4} #ciag od 5 znak
echo ${napis:1:6} #7znakow od 2 znaku poczawszy
echo ${napis//a/b} #wszystkie litery a zostaly zamienione
echo ${napis/a/b} #pierwsza litera a zostala zamieniona na b
