#!/bin/bash

# Double-Parentheses Construct

	x=1
	y=1

	while [ $x -lt 9 ]; do
		echo $x $y
		x=$(( $x + 1 ))
		y=$(( $y * 2 ))
	done

exit 0

