#!/bin/bash
file=1Corr
gcc -Wall -O3 -o $file.e $file.c -lm
rm ./Prob_Acep/Prob_Acep.txt
./$file.e
