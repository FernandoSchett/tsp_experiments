#!/bin/bash

inst="kroA100 si1032 st70"
alphas="0.01 0.025 0.05 0.1"

for i in $inst
do
    mkdir $i
    cd $i
    for alp in $alphas
    do
        mkdir $alp
        cd $alp
        perl ../../tttplots.pl -f ${i}_${alp}
        # touch ${i}_${alp}.dat
        cd ..
    done
    cd ..
done