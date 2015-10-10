for host in 4 12 1 11
do
	if ping -c1 10.130.0.$host
        then
           echo 10.130.0.$host est vivant
        else
           echo 10.130.0.$host est mort
        fi
done
