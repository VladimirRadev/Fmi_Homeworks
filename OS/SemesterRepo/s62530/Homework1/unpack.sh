#!/bin/bash
# $1 -> .zip
# $2 -> ok/
# $3 -> failed/
# $4 -> flags.txt

#exit 1 : num of arguments error
#exit 2 : value of arguments error
#exit 3 : not right format of givenZipFile

if ! [ $# -eq 4 ]; then
	echo "4 arguments must be provided"
	exit 1
fi
#r=$1 
#ls -lhr "${1}"
r1=$(basename "${1}")
l1=$( find ./ -name "${r1}" | wc -l )
if [[ $l1  -eq 0 ]] || [[ $(find ./ -mindepth 1 -name "$(basename "${2}")" | wc -l) -eq 1 ]] || [[ $(find ./ -mindepth 1 -name "$(basename "${3}")" | wc -l ) -eq 1 ]] || [[ $(find ./ -mindepth 1 -name "$(basename "${4}")" | wc -l ) -eq 1 ]];then
	echo "Some of the arguments is existing/not existing"
	exit 2
fi
mkdir $2 $3
touch $4
unzip "${1}" -d /tmp/xtDir 2>/dev/null 1>/dev/null
if [ $? -ne 0 ];then
	echo "The "${1}" is not in right format "
	exit 3
fi
#find /tmp/xtDir -mindepth 1 -maxdepth 1 -type d | xargs -I {}  basename {}

while IFS='-' read name; do

	archive=$(find /tmp/xtDir/$name* -mindepth 1 -type f | rev | sed -e "s/\/.*//" | rev )
	moreThanAFileInMoodle=0

	#More than a file submitted in moodle
	if [[ $(echo $archive | wc -l ) -gt 1 ]]; then
		moreThanAFileInMoodle=1
		cp -r /tmp/xtDir/$name*/ $3/$name/
		continue 2
	fi

   #echo $archive | grep -E -v "^$name" | xargs -I {} echo $name {}

   echo $archive | sed -e 's/\s*$//g' |  grep -Ev -q '.tar$|.tar.gz$|.tar.xz$|.tar.bz2$|.zip$|.rar$'

   # Archive doesn't match any of above listed ( Example: *.docs)
   if [[ $? -eq 0 ]];then
		cp -r /tmp/xtDir/$name*/ $3/$name/
		continue 2 
   fi

 
	wrongArchiveFn=$(echo $archive | grep -Ev "^$name." | wc -l)
	wrongArchiveExtension=$(echo $archive | grep -Ev "$name.tar.xz$" | wc -l)


	######## za result.txt otiva tova 
	fn="${name}"
	gri=0
	grf=0
	nd=0
	grd=0
	###################

	if [[ $wrongArchiveFn -eq 1 || $wrongArchiveExtension -eq 1 ]];then
		gri=1
	fi

	#we are sure at this stage of the program that only a single file can reach 
	fileToExt=$(find /tmp/xtDir/$name* -mindepth 1 -type f -printf "%p")
	fileDescription=$(file -z $fileToExt)
	
	############################
	echo $fileDescription | grep -Eq 'compressed data'
	if [ $? -eq 0 ]; then


		############################
		echo $fileDescription | grep -Eq '.*XZ compressed data.*'
		if [ $? -eq 0 ]; then
			unxz $fileToExt 2> /dev/null
			
			# dearchivator ERROR - > send to failed/
			if [ $? -ne 0 ];then
				mkdir $3/$name
				mv /tmp/xtDir/$name*/* $3/$name
				continue
			fi
			fileToExt=$(echo $fileToExt | sed -e 's/.xz$//g')
			fileDescription=$(file -Z $fileToExt)
			

			############################
			echo $fileDescription | grep -Eq 'tar'
			if [ $? -eq 0 ];then
			    mkdir -p /tmp/work/$name
				tar -C /tmp/work/$name  -xvf $fileToExt 1>/dev/null 2>/dev/null 

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi
				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi	
		
		   #za zip unxztnat veche 
		
	   		############################	   
			echo $fileDescription |  grep -Eq '.*Zip archive .*'
		    if [ $? -eq 0 ];then

				grf=1
				
			    mkdir -p /tmp/work/$name
				unzip $fileToExt -d /tmp/work/$name 1>/dev/null 2>/dev/null

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi	
		

	
		  		 #za rar unxztnat veche

		   	############################	
		    echo $fileDescription | grep -Eq '.*RAR archive .*'
			if [ $? -eq 0 ];then
				grf=1
				
				
			    mkdir -p /tmp/work/$name
				unrar x $fileToExt /tmp/work/$name 1>/dev/null 2>/dev/null
				
				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)

				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel

				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue
			fi

	   					   
		fi


		############################
		echo $fileDescription | grep -Eq '.*bzip2 compressed data.*'
	   	if [ $? -eq 0 ]; then
			
	    	grf=1

		   	bzip2 -vd $fileToExt 1>/dev/null 2>/dev/null
			# dearchivator ERROR - > send to failed/
			if [ $? -ne 0 ];then
				mkdir $3/$name
				mv /tmp/xtDir/$name*/* $3/$name
				continue
			fi	

			#bzip2 option is to create anyothername file ( like .tar.xz for example to anyothername.out, with the line down i return it to its original name )
			mv $fileToExt* $fileToExt 
			fileToExt=$(echo $fileToExt | sed -e 's/.bz2$//g')
			fileDescription=$(file -Z $fileToExt)
			
			#za tar unbzip2tnat veche


			############################

			echo $fileDescription | grep -Eq 'tar'
			if [ $? -eq 0 ];then
			    mkdir -p /tmp/work/$name
				tar -C /tmp/work/$name  -xvf $fileToExt 1>/dev/null 2>/dev/null 

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi
				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
  					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi


			
			#za zip unbzip2tnat veche


			############################	   
			echo $fileDescription |  grep -Eq '.*Zip archive .*'
		    if [ $? -eq 0 ];then
				
			    mkdir -p /tmp/work/$name
				unzip $fileToExt -d /tmp/work/$name 1>/dev/null 2>/dev/null

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi	
		
			
			#za rar unbzip2tnat veche



			############################
		    echo $fileDescription | grep -Eq '.*RAR archive .*'
			if [ $? -eq 0 ];then
				grf=1


			    mkdir -p /tmp/work/$name
				unrar x $fileToExt /tmp/work/$name 1>/dev/null 2>/dev/null

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)

				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel

				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue
			fi
	   fi


		############################
		echo $fileDescription | grep -Eq '.*gzip compressed data.*'
 		if [ $? -eq 0 ];then
			grf=1


			suf=$(echo "$(basename $fileToExt)" | sed -e 's/.*\././' )	
			gzip -d $fileToExt -S $suf 1>/dev/null 2>/dev/null

			# dearchivator ERROR - > send to failed/
			if [ $? -ne 0 ];then
				mkdir $3/$name
				mv /tmp/xtDir/$name*/* $3/$name
				continue
			fi	
			


				
			fileToExt=$(echo $fileToExt | sed -e "s/$suf$//g")
		   	fileDescription=$(file -Z $fileToExt)

			#za tar ungzipnat veche 

			############################
			echo $fileDescription | grep -Eq 'tar'
			if [ $? -eq 0 ];then
			    mkdir -p /tmp/work/$name
				tar -C /tmp/work/$name  -xvf $fileToExt 1>/dev/null 2>/dev/null 
				
				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi
				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi


			#za zip ungzipnat veche

			############################	   
			echo $fileDescription |  grep -Eq '.*Zip archive .*'
		    if [ $? -eq 0 ];then

				grf=1

			    mkdir -p /tmp/work/$name
				unzip $fileToExt -d /tmp/work/$name 1>/dev/null 2>/dev/null


				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi

				echo "$name"


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi	
		



			#za rar ungzipnat veche

			############################	
		    echo $fileDescription | grep -Eq '.*RAR archive .*'
			if [ $? -eq 0 ];then
				grf=1
				
				
			    mkdir -p /tmp/work/$name
				unrar x $fileToExt /tmp/work/$name 1>/dev/null 2>/dev/null
				
				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)

				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel

				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue
			fi
			
				
		fi
	fi



		#tuka sa sluchaite ako ne e kompresiran  fail no e archive


		############################
		echo $fileDescription | grep -Ev 'compressed data' | grep -Eq 'archive'	
		if [ $? -eq 0 ];then
			grf=1

			#za tar archive
			############################


			echo $fileDescription | grep -Eq '.* tar .*'
			if [ $? -eq 0 ];then
			    mkdir -p /tmp/work/$name
				tar -C /tmp/work/$name  -xvf $fileToExt 1>/dev/null 2>/dev/null 

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then

					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi
				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi	


			#za zip archive


			############################	   
			echo $fileDescription |  grep -Eq '.*Zip archive .*'
		    if [ $? -eq 0 ];then

				grf=1
				
			    mkdir -p /tmp/work/$name
				unzip $fileToExt -d /tmp/work/$name 1>/dev/null  2>/dev/null

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then

				  				
					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)
				
				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel
				
				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0	
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/	
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue	
			fi	
		

	

			#za rar archive
			
			############################
			echo $fileDescription | grep -Eq '.*RAR archive .*'
			if [ $? -eq 0 ];then
				grf=1


			    mkdir -p /tmp/work/$name
				unrar x $fileToExt /tmp/work/$name 1>/dev/null 2>/dev/null

				# dearchivator ERROR - > send to failed/
				if [ $? -ne 0 ];then

					mkdir $3/$name
					mv /tmp/xtDir/$name*/* $3/$name
					continue
				fi


				thingsOnfirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 | wc -l)
				folderOnFirstLevel=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d | wc -l)

				dirWithRightName=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -name $name -printf "%P")
				folderOnSecondLevel=$(find /tmp/work/$name/$name -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l)
				#echo $folderOnSecondLevel

				if [[ $dirWithRightName  ==  $name ]] && [[ $thingsOnfirstLevel -gt 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#ls -lhr $2/
				elif [[ $folderOnFirstLevel -eq 0 ]] && [[ $thingsOnfirstLevel -ge 1 ]];then
					nd=1
					grd=1
					mv /tmp/work/$name $2/
					#ls -lhr $2/
					#echo -n "2) " ; ls -lhr $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $thingsOnfirstLevel -eq 1 ]];then
					nd=0
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "4) \n"

				elif [[ $dirWithRightName != $name ]] && [[ $folderOnFirstLevel -ge 1 ]];then
					nd=0
					grd=1
					mvTo=$(find /tmp/work/$name -mindepth 1 -maxdepth 1 -type d -printf "%P" | head -n 1)
					mv /tmp/work/$name/$mvTo /tmp/work/$name/$name
					mv /tmp/work/$name/$name $2/
					#echo -en "5)  $name \n"
					#find $2/$name
				elif [[ $dirWithRightName == $name ]] && [[ $folderOnSecondLevel -gt 0 ]];then
					nd=1
					grd=0
					mv /tmp/work/$name/$name $2/
					#echo -en "6) $name \n"
					#find $2/$name
				fi

				rm -r /tmp/work

				echo "$fn $gri $grf $nd $grd" >> $4
			   continue

			fi
		    
		fi

		
		#if anything reaches this stage of the program have to  be treated as failed

		mkdir $3/$name
		mv /tmp/xtDir/$name*/* $3/$name
		continue

	

done < <(find /tmp/xtDir -mindepth 1 -maxdepth 1 -type d | xargs -I {} basename {}| sed -e 's/-.*//')

tempF=$(mktemp)
sort $4 > $tempF
cat $tempF > $4

#cat $4

#find $2 -mindepth 1 -maxdepth 1 -type d | wc -l -> It has to be 212

#find $3 -mindepth 1 -maxdepth 1 -type d | wc -l - > It has to be 1
rm $tempF
rm -r /tmp/xtDir 
#rm -r ./$2 ./$3 ./$4



