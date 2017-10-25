for toto in $(cat ${1:-/dev/stdin})
do
	ping -c1 $toto
done
