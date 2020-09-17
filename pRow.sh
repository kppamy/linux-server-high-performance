#!/bin/bash
awk 'NR==10{print}' file_10.txt
sed -n 10p file_10.txt
tail -n+10 file_10.txt|head -n 1
