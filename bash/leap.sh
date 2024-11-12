#!/bin/bash


echo "Enter a number:"
read num

if [ $num -lt 0 ]; then
exit 0
fi

prod=1
for (( i=1 ; i<=num ; i++ )); do
    prod=$((prod * i))

done
echo $prod