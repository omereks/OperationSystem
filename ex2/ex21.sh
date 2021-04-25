#!/bin/bash
# Omer Eckstein 312350192

#paramtert $1 is path to dir
#paramtert $2 is file type
#paramtert $3 is word

#check if have 3 parameters
if test $# -le 2
then
    echo "Not enough parameters"
    exit 1
fi


#get in the directory in $1
cd $1
#all the things in $1 directory sorted
DIR=$(ls | sort -V)

#loop for printing the txt files
for FILE in $DIR -v
do
    #in case that $FILE is file in kind of .$2
    case $FILE in *.$2) 
        grep -iwh $3 $FILE
        #awk  '/'"$3 -i"'/ {print}' $FILE
    esac
done

