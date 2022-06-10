#!/bin/bash

FILE=./filter

if [ -f "$FILE" ]; then
   rm ./filter
fi
cc     filter.c helpers.c  -o filter -lcs50
./filter "$@"
