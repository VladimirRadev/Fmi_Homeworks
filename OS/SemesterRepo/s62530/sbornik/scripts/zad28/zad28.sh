#!/bin/bash

if [ $# -ne 2 ];then
	echo "Program must take 2 arguments in this format: <dirName> <lookingForStr>"
	exit 1
fi

dir="${1}"
str="${2}"
find "${dir}" -mindepth 1 -maxdepth 1 -type f | sed -E "s/^.*\///g" |grep -E  "^vmlinuz-[0-9]+\.[0-9]+\.[0-9]+-${str}" | sort -r -t '-' -k 2,2 | head -n 1
