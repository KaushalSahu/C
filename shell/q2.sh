#!/bin/bash

a=1
b=2
c=3
 
if [ $a -gt $b -a $a -gt $c ];
then
    echo "$a is Greatest"
elif [ $b -gt $c -a $b -gt $a ];
then
    echo "$b is Greatest"
else
    echo "$c is Greatest!"
fi
