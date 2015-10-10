if test $# -eq 2 
then
	echo $[$1+$2]
else
	echo Entrer valeur1
	read p1
	echo Entrer valeur2
	read p2
	echo $[$p1+$p2]
fi


