#!/bin/bash
awk '{for(i=1;i<=NF;i++){dc[$i]++;}} END{for(key in dc){print key,dc[key] }}' $1 |sort -k 2 -nr
#for file in $( ls words*.txt );do ./words.sh $file;echo -e '============\n\r';done
