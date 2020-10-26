#!/bin/bash
sed 's/^ *//' $1|awk '{print $0,";"}'
