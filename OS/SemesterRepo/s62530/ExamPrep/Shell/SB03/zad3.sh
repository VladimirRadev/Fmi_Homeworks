#!/bin/bash

#a)
find . -empty | xargs -I {} rm -r {}

#b)
find ~ -user $(id -un) -type f -printf  "%s %p\n" | sort -rn -t ' ' -k 1,1 | head -n 5 | sed -E 's/^[0-9]+ //' | xargs -I {} rm -ri {}
