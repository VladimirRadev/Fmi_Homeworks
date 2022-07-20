#!/bin/bash
echo "$#"
if [ ${#} -gt 1 ] || [ ${#} -eq 0 ]; then
	echo "Wrong Input"
	exit 1
fi

if [[ $1 =~ ^[a-zA-Z0-9]*$ ]] && [[ -n $1 ]]; then
	echo "alphanum"
	else
	echo "greshka"
fi	
	
