#!/bin/bash

if [ $# -ne 3 ];then
	echo -en "Arguments must be in this format: ./program.sh <file> <string1> <string2> \n"
	exit 1
fi


fileName="${1}"
str1="${2}"
str2="${3}"

storeStr1=$(mktemp);
storeStr2=$(mktemp);
cat $fileName | grep -E "${str1}=" | sed -E 's/^.*=//' | tr -s ' ' | tr ' ' '\n' | sort | uniq | tr -s ' ' > $storeStr1

grep -Eq "${str2}" $fileName

#file do contain str2
if [ $? -eq 0 ];then
	cat $fileName | grep -E "${str2}=" | sed -E 's/^.*=//' | tr -s ' ' | tr ' ' '\n' | sort | uniq | tr -s ' ' > $storeStr2
	
# 	cat $storeStr2 		
	while read char;do
		
		grep -Eq "^$char" $storeStr1

		if [ $? -eq 0 ];then

			sed -Ei "s/^${char}$//g" $storeStr2 
		fi

				
	done < <(cat $storeStr2)

	outLineStr1=$(cat $storeStr1 | tr '\n' ' ' | tr -s ' ' | sed -E 's/^ +//')
	outLineStr2=$(cat $storeStr2 | tr '\n' ' ' | tr -s ' ' | sed -E 's/^ +//')

	#echo -en "$outLineStr1$outLineStr2\n"	
	#cat $fileName

	sed -Ei "s/^(${str1}=).*/\1${outLineStr1}/" $fileName
	sed -Ei "s/^(${str2}=).*/\1${outLineStr2}/" $fileName

	#cat $fileName
else
	outLineStr1=$(cat $storeStr1 | tr '\n' ' ' | tr -s ' ' | sed -E 's/^ +//')
	outLineStr2=""
	
	sed -Ei "s/^(${str1}=).*/\1${outLineStr1}/" $fileName
	echo -en "${str2}=$outLineStr2\n" >> $fileName

fi


rm -r $storeStr1 $storeStr2





