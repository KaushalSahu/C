#!/bin/bash

	x=1

	for x in `ls`; do
		if [ $x == "q5.sh" ]; then
			break;
		else
			echo $x
		fi
	done

exit 0
