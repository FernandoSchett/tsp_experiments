#!/bin/bash

cd ..
inst=("kroA100.tsp" "si1032.tsp")
look4=("21282" "92650") 
time="600"
alphas="0.010000 0.025000 0.050000 0.100000"

mkdir tttplots

for alp in $alphas
do
    for s in $(seq 1 50)
    do
        dir_with_time="grasp_t${time}_a${alp}_s${s}"
        dir="grasp_a${alp}_s${s}"
        awk -v var=";${s}" '{print $0 var}' "./results/${dir}/time_result.txt" > "./results/${dir}/tmp.txt"
        cat ./results/${dir}/tmp.txt | grep kroA100 >> tttplots/time_result.txt
        cat ./results/${dir}/tmp.txt | grep si1032 >> tttplots/time_result.txt
        cat ./results/${dir}/tmp.txt | grep st70 >> tttplots/time_result.txt
        rm ./results/${dir}/tmp.txt
    done
done

