#!/bin/bash

	for x in `ls`; do
		if [ $x == "shell_29.sh" ]; then
			continue
		fi
		echo $x
	done

exit 0

