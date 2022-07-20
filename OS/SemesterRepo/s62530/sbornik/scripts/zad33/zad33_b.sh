#!/bin/bash
nums=$(mktemp)
grep -E '^\-?[0-9.]'  > $nums

maxSum=$(cat $nums | tr -d '.' | tr -d '-' | sed -E 's/([0-9]{1})/\1 /g ' | sed -E 's/\s{1,}$//g' |sed -E 's/ / + /g'  | bc | sort -rn | head -n 1 )


lowestSumNums=$(mktemp)
while read num; do
	cur=$(echo $num | tr -d '.' | tr -d '-' | sed -E 's/([0-9]{1})/\1 /g ' | sed -E 's/\s{1,}$//g' |sed -E 's/ / + /g'  | bc )
	if [ $cur -eq  $maxSum ]; then
		echo -en  "${num}\n" >> $lowestSumNums
	fi
done < <(cat $nums)
cat $lowestSumNums | sort -n | head -n 1
rm -r $nums $lowestSumNums

