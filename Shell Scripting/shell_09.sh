#!/bin/bash

	for x in `ls`; do
		if [ $x == "shell_05.sh" ]; then
			break
		fi
		echo $x
	done

exit 0

