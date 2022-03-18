#!/bin/bash

cc     runoff.c   -o runoff -lcs50
./runoff "$@"
