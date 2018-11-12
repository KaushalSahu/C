#!/bin/bash

	echo 'cat ../data/matrix | sort -k 3'
	cat ../data/matrix | sort -k 3
	echo

	echo 'cat ../data/matrix | sort -k 3n -k 2'
	cat ../data/matrix | sort -k 3n -k 2
	echo

	echo 'cat ../data/matrix | sort -k 3nr'
	cat ../data/matrix | sort -k 3nr

exit 0

