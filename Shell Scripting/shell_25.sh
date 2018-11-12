#!/bin/bash

	for file in `ls *_2?.sh | tail -2`; do
		ls -l $file
		ls -l $file | tr [a-kw] [A-K#]
		ls -l $file | sed 's/sh/SY/'
		echo
	done

exit 0

