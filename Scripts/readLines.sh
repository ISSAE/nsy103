while read input 
do
    echo $input
done < ${1:-/dev/stdin}

