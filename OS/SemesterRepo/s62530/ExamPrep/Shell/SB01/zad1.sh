#!/bin/bash

grep -E '[02468]'  philip-j-fry.txt | grep -vc '[a-w]' 
