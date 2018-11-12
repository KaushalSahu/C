#!/bin/bash

	declare -A arr

	for file in `ls`; do
		arr[$file]=`ls -l $file | awk '{print $5}'`
	done

	for file in `ls`; do
		echo "$file -> ${arr[$file]} bytes"
	done

exit 0

