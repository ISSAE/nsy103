i=0
for x in $*
do
        let i=i+1
        echo param $i 
	echo $x
done
