#!/bin/sh

nbre=0
compteur=0
un=1
val=$1

while (($compteur<=$val))
do
	nbre=$((nbre+compteur))
	compteur=$((compteur+un))
done

#for compteur in $((val))
#do
#	nbre=$((nbre+compteur))	
#	compteur=$((compteur+un))
#done

#echo "$compteur"
#echo "$nbre"
