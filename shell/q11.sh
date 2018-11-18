#!/bin/bash

sum()
{
	x=$1
	y=$2

	return $(( $x + $y ))
}

function add
{
	x=$1
	y=$2

	return $(( $x + $y ))
}

sum 7 5
	echo "$?"

add 7 9
	echo "$?"

exit 0
