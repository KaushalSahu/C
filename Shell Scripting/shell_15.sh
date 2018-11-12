#!/bin/bash

duplicate()
{
	x="shell_15.sh"
	for y in `ls`; do
		diff $x $y > /dev/null
		if [ $? -eq 0 ] && [ $x != $y ]; then
			echo $x and $y are same
		fi
	done
}

	duplicate

exit 0

