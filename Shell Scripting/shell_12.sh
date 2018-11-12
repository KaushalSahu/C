#!/bin/bash

fact()
{
	x=$1
	f=1
	while [ $x -gt 1 ]; do
		f=$(($f * $x))
		x=$(($x - 1))
		echo $x $f
	done

	return $f
}

	fact 5
	echo "fact(5) = $?"

exit 0

