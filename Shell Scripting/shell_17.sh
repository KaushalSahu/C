#!/bin/bash

	cd ../2D\ Arrays/

	c_file=`ls *.c`
	i_file=`ls *.ip`

	echo Found C program $c_file
	echo Found input file $i_file
	echo

	gcc $c_file
	./a.out < $i_file > out

	echo The program printed:
	cat ../data/out

	rm -f ../data/a.out ../data/out

exit 0

