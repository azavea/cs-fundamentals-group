#!/bin/bash

cc     caesar.c   -o caesar -lcs50
./caesar "$@"
