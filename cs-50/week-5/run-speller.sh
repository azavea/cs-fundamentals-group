#!/bin/bash

cc     speller.c dictionary.c  -o speller -lcs50
./speller "$@"
