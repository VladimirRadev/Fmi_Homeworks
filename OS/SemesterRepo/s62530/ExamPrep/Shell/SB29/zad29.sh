#!/bin/bash

if [ $# -ne 0 ] ;then
	echo "Program mustn't take arguments"
	exit 1;
fi

pS=$(mktemp)
processes=$(mktemp)
users=$(mktemp)
ps -eo user=,pid=,rss= > $pS
cat $pS | grep -Ev "root" > $processes
cat $processes | cut -d ' ' -f 1,1 | sort | uniq > $users

rootTotalRSS=$(cat $pS | grep -E '^root' | awk -F ' ' -v "var=0" '{var+=$3} END{print var}')

while read user;do
	
	if [[ $(stat $(cat /etc/passwd | grep -E "^$user" | cut -d ':' -f 7 ) 2> /dev/null | wc -l) -eq 0 ]] || [[  $(stat $(cat /etc/passwd | grep -E "^$user" | cut -d ':' -f 7 ) --printf "%U" ) != $user ]] || [[ $(stat $(cat /etc/passwd | grep -E "^$user" | cut -d ':' -f 7 ) --printf "%A\n" | cut -c 2-4 | grep -E 'w' | wc -l ) -ne 1 ]];then
		
		if [[ $(cat $processes | grep -E "^${user}" | awk -F ' ' -v "var=0" '{var+=$3} END{print var}' ) -gt $rootTotalRSS  ]];then
		#echo "kr"			
		#cat $processes | grep -E "^${user}" | awk -F ' ' '{print $2}' | xargs -I {} kill -9 {} 
		killall -u "${user}" 
		sleep 2
		killall -u "${user}" -KILL 

		fi
		
		
	fi

	continue;
			

done< <(cat $users)
