for toto in $(cat $1)
do
	ping -c1 $toto
done
