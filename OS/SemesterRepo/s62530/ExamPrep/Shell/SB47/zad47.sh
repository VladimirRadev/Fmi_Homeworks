#!/bin/bash

if [ $# -ne 2 ];then
	echo "Program must take 2 arguments in format: <srcDir> <destDir>"
	exit 1
fi

src="${1}"
dest="${2}"

if [[ $(stat ${src} 2>/dev/null | wc -l) -eq 0 ]];then
	echo "Source dir doesn't exist: ${src}"
	exit 2
fi

if [[ $(stat ${dest} 2>/dev/null | wc -l) -eq 0  ]] || [[ $(find $dest -mindepth 1 2>/dev/null | wc -l) -ne 0 ]];then
	echo "Destination dir is not empty or it doesn't exist ${dest}"
	exit 3
fi

files=$(mktemp)
trash=$(mktemp)
find "${src}" -type f 2>/dev/null | sort  > $files
	
while read file;do
	baseName=$(echo "${file}" | sed -E "s/${src}\///g")
	
	base=$(echo "${file}" | sed -E 's/.*\/(.*)$/\1/g')

	cat $files | sed -E 's/.*\/(.*)$/\1/g' | grep -Eq "\.${base}\.swp" 	
	if [[ $(echo ${?}) -eq 0 ]];then
		#echo "Trash"
		echo ".${base}.swp" >> $trash
	fi
	
	
	grep -Eq "^${base}" $trash
	
	if [ $(echo "${?}") -eq 0 ];then
		#echo "stignahme trash ${file}"
		continue
	fi
	#file has a dir parent
	if [[ $(echo "$(dirname "${baseName}")") != "." ]];then
		echo "purvi if ${baseName}"

		mkdir -p "${dest}/"$(dirname "${baseName}")""
		tree dir2
		cp -v -- "${file}" "${dest}/$(dirname "${basename}")/"
	else
			echo "vtori if ${base}"
			cp -v -- "${file}" "${dest}"
	fi

	#mkdir -p "${dst}/$(dirname "${baseName}")"
	#echo "$(dirname ${baseName})"

done < <(cat $files)
