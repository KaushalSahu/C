#!/bin/bash

	n=5
	for ((i = 0; i < n; i++)) do
		arr[$i]=$(( $i * 2 ))
	done

	for ((i = 0; i < n; i++)) do
		echo "arr[$i] = " ${arr[$i]}
	done

exit 0
