#!/bin/bash
nums=$(mktemp)
grep -E '^\-?[0-9\.]' > $nums
#cat $nums
maxNum=$(cat $nums | sort -rn | head -n 1)
#echo -en "$maxNum\n"
cat $nums | grep -E  "^\-?$maxNum" | sort | uniq 
rm -r $nums
