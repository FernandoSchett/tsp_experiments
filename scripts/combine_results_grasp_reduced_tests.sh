#!/bin/bash

# ==============================================
# Script Name:    combine_results_grasp_reduced_tests.sh
# Description:    Combine results from reduced tests GRASP PR to one file
# Author:         Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
# Created Date:   22/07/2024
# ==============================================

cd ..
inst=("rl1304.tsp" "u1060.tsp" "fl1400.tsp") 
#inst=("brd14051.tsp d15112.tsp d18512.tsp")
#inst=("kroA100.tsp" "si1032.tsp")
look4=("280207" "246164" "20977")
#look4=("530512" "1769898" "733473") 
#look4=("21282" "92650") 
time="600"
alphas="0.050000"
modes="b" 
#alphas="0.010000 0.025000 0.050000"

mkdir tttplots

for mod in $modes
do
    for s in $(seq 1 100)
    do
        dir="grasp_prr_b_t600_a0.050000_s${s}"
        awk -v var=";${s}"  '{print $0 var}' "./results/${dir}/time_result.txt" > "./results/${dir}/tmp.txt"
        #var=$(awk 'NR <= 3' ./results/${dir}/tmp.txt)
        #echo $var >> tttplots/time_result_forward.txt
        #ar=$(awk 'NR >= 7 && NR <= 9' ./results/${dir}/tmp.txt)
        #echo $var >> tttplots/time_result_backward.txt
        var=$(awk 'NR >= 4 && NR <= 6' ./results/${dir}/tmp.txt)
        echo $var >> tttplots/time_result_prr_100_backward.txt
        var=$(awk 'NR >= 13 && NR <= 15' ./results/${dir}/tmp.txt)
        echo $var >> tttplots/time_result_prr_200_backward.txt        
        #cat ./results/${dir}/tmp.txt | grep rl1304 >> tttplots/time_result.txt
        #cat ./results/${dir}/tmp.txt | grep u1060 >> tttplots/time_result.txt
        #cat ./results/${dir}/tmp.txt | grep fl1400 >> tttplots/time_result.txt
        #rm ./results/${dir}/tmp.txt
    done
done



#for mod in $modes
#do
    #for s in $(seq 36 100)
    #do
        #dir="grasp_pr_a0.050000_s${s}"
        #awk -v var=";${s}"  '{print $0 var}' "./results/${dir}/time_result.txt" > "./results/${dir}/tmp.txt"
        #var=$(awk 'NR <= 3' ./results/${dir}/tmp.txt)
        #echo $var >> tttplots/time_result_forward.txt
        #var=$(awk 'NR >= 4 && NR <= 6' ./results/${dir}/tmp.txt)
        #echo $var >> tttplots/time_result_backward.txt
        #var=$(awk 'NR >= 7 && NR <= 9' ./results/${dir}/tmp.txt)
        #echo $var >> tttplots/time_result_forward_backward.txt        
        #cat ./results/${dir}/tmp.txt | grep rl1304 >> tttplots/time_result.txt
        #cat ./results/${dir}/tmp.txt | grep u1060 >> tttplots/time_result.txt
        #cat ./results/${dir}/tmp.txt | grep fl1400 >> tttplots/time_result.txt
        #rm ./results/${dir}/tmp.txt
    #done
#done