#!/bin/bash
# ==============================================
# Script Name:    run_grasp_pr_reduced_tests.sh
# Description:    Run GRASP + Path Relinking heuristic on Reduced Tests and create logs and results
# Author:         Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
# Created Date:   22/07/2024
# How to run it:  ./run_grasp_pr_reduced_tests.sh
# ==============================================

cd ..
#inst=("fl1400.tsp")
inst=("rl1304.tsp" "u1060.tsp" "fl1400.tsp") # inst=("kroA100.tsp" "si1032.tsp") 
look4=("280207" "246164" "20977") # look4=("21282" "92650")
#look4=("20977")
time="600" 
alphas="0.050000"

make clean
make 

for alp in $alphas
do
    for s in $(seq 94 94)
    do
        dir="grasp_pr_fb_t${time}_a${alp}_s${s}"

        mkdir benchmark/logs/${dir}
        mkdir results/${dir}

        echo "--------------- Running reduced tests GRASP PR with two_opt_first_imprv_circ_search and alpha = $alp and seed = $s" >> ./results/${dir}/time_result.txt
        date >> ./results/${dir}/time_result.txt
        echo $USER >> ./results/${dir}/time_result.txt

        for i in $(seq 0 $((${#inst[@]} - 1)))
        do
            path=./benchmark/instances/chosen_inst/${inst[$i]} 
            echo "./TSP -f  $path -p look4 -o ${look4[$i]} -t $time -c grasp_pr -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search -g bf -k 10 >> benchmark/logs/${dir}/${inst[$i]}.txt" 
            ./TSP -f  $path -p look4 -o ${look4[$i]} -t $time -c grasp_pr -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search -g bf -k 10 >> benchmark/logs/${dir}/${inst[$i]}.txt
        done

        date >> ./results/${dir}/time_result.txt
        echo $USER >> ./results/${dir}/time_result.txt
        echo "---------------" >> ./results/${dir}/time_result.txt
    done
done
