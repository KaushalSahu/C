#!/bin/bash

function fact
{
	if (( $1 < 2 )); then
		echo 1
	else
		echo $(( $1 * $(fact $(( $1 - 1 ))) ))
	fi
}

	x=6
	f=`fact $x`
	echo "fact($x) = $f"

exit 0

