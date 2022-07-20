#!/bin/bash

if [ $# -ne 3 ]; then
	echo "program must take 3 arguments in format: <num> <prefixSymbol> <unitSymbol>"
	exit 1
fi	

bases="base.scv"
prefixes="prefix.scv"

num="${1}"
prefixSym="${2}"
unitSym="${3}"

grep -Eq "^.*,${prefixSym},.*$" $prefixes

if [ $? -ne 0 ];then
		echo "${prefixSym} doesn't appear in $prefixes file"
		exit 2
fi

grep -Eq "^.*,${unitSym},.*$" $bases

if [ $? -ne 0 ];then
		echo "${unitSym} doesn't appear in $bases file"
		exit 3
fi


awk -F ',' -v "decimal=$(grep -E "^.*,${prefixSym},.*$" $prefixes | cut -d ',' -f 3)" -v "input=${num}" -v "unit=${unitSym}" 'BEGIN{input=input*decimal} {if($2==unit){printf("%1.1f %s (%s, %s)\n",input,unit,$3,$1)}}' $bases




