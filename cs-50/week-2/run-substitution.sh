#!/bin/bash

cc     substitution.c   -o substitution -lcs50
./substitution "$@"
