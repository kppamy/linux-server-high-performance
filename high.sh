#!/bin/bash
start=$(date +%s);for((i=0;i<500;i++));do (echo $i;sleep 0.05;./socket_client 127.0.0.1 5555 &); done;echo "cost" $(( $(date +%s) - $start )) "s";
