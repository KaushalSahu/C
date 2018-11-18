#!/bin/bash

	x=1
	y=2

	until [ $x -eq 9 ]; do
		echo $x $y
		x=$(( $x + 1 ))
		y=$(( $y * 2 ))

	done

exit 0
