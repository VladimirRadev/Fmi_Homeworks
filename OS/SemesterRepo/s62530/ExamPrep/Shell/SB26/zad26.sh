#!/bin/bash

#a)
users=$(mktemp)
processes=$(mktemp)
userProcesses=$(mktemp)
ps -eo uname,uid,pid,rss > $processes
cat $processes | cut -d ' ' -f1,1 | sort | uniq -c | tr -s ' ' | sed -E 's/^ {1,}//' | sed -E 's/ {1,}$//g' > $userProcesses

while read countProcesses user;do
	totalRSS=$(grep -E "$user" $processes | awk -F ' ' -v "var=0" '{var+=$4} END{print var}')
	echo  "${user} ${countProcesses} ${totalRSS}"
done < <(cat $userProcesses)


echo -en "\n\n\n\n\n\nkurrrrr\n\n\n"
#b)



while read countProcesses user;do
	totalRSS=$(grep -E "$user" $processes | awk -F ' ' -v "var=0" '{var+=$4} END{print var}')
	#echo  "${user} ${countProcesses} ${totalRSS}"

	avg=$(echo $count | awk -F ' ' -v "v1=$totalRSS" -v "v2=$countProcesses" -v "v3=0" '{v3=v1/v2} END{print v3}')
	avg1=$(echo $avg | sed -E 's/\..*//g')
	biggestRssUsageProcess=$(
	grep -E "$user" $processes | tail -n +2 | tr -s ' ' | cut -d ' ' -f 3,4 | sed -E 's/^$//g' | tr -s '\n' | sort -rn -k 2,2 | head -n 1
)
	v=$(echo $biggestRssUsageProcess | tr -s ' ' | cut -d ' ' -f 2) 
	g=$(echo "2 * ${avg1}" | bc)
	if [[  ${v} -ge ${g}  ]] ;then
		echo -en "kiling process with pid: $(echo $biggestRssUsageProcess | awk -F ' ' '{print $1}')\n"
		kill -s SIGTERM $(echo $biggestRssUsageProcess | awk -F ' ' '{print $1}')
		sleep 2
		kill -s SIGKILL  $(echo $biggestRssUsageProcess | awk -F ' ' '{print $1}')

	fi

	#echo $biggestRssUsageProcess
done < <(cat $userProcesses)

