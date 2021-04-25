#!/bin/bash
# Omer Eckstein 312350192

recursiveFunc() {
    $5/ex21.sh $1 $2 $3 | awk -v NUM=$4 'NF>=NUM'
    cd $1
    for DIR in $(ls -d */ 2>/dev/null | sort -V)
    do
        recursiveFunc $DIR $2 $3 $4 $5
        #echo $DIR
    done
    cd ..
}

#paramtert $1 is path to dir
#paramtert $2 is file type
#paramtert $3 is word
#paramtert $4 is num

#check if have 4 parameters
if test $# -le 3
then
    echo "Not enough parameters"
    exit 1
fi

#./ex21.sh $1 $2 $3 | awk -v NUM=$4 'NF>=NUM'
recursiveFunc $1 $2 $3 $4 $PWD

