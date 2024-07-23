#!/bin/bash

# ==============================================
# Script Name:    run_grasp_reduced_tests.sh
# Description:    Run GRASP + Path Relinking + Reestart heuristic on Reduced tests and create logs and results
# Author:         Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
# Created Date:   22/07/2024
# ==============================================

cd ..
inst=("fl1400.tsp")
#inst=("rl1304.tsp" "u1060.tsp" "fl1400.tsp") # inst=("kroA100.tsp" "si1032.tsp") 
look4=("20977")
#look4=("280207" "246164" "20977") # look4=("21282" "92650")
time="600" 
alphas="0.050000"

make clean
make 

for alp in $alphas
do
    for s in $(seq 94 84)
    do
        dir="grasp_t${time}_a${alp}_s${s}"

        mkdir benchmark/logs/${dir}
        mkdir results/${dir}

        echo "--------------- Running reduced tests GRASP with two_opt_first_imprv_circ_search and alpha = $alp and seed = $s" >> ./results/${dir}/time_result.txt
        date >> ./results/${dir}/time_result.txt
        echo $USER >> ./results/${dir}/time_result.txt

        for i in $(seq 0 $((${#inst[@]} - 1)))
        do
            path=./benchmark/instances/chosen_inst/${inst[$i]} 
            echo "./TSP -f  $path -p look4 -o ${look4[$i]} -t $time -c grasp -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search >> benchmark/logs/${dir}/${inst[$i]}.txt" 
            ./TSP -f  $path -p look4 -o ${look4[$i]} -t $time -c grasp -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search >> benchmark/logs/${dir}/${inst[$i]}.txt
        done

        date >> ./results/${dir}/time_result.txt
        echo $USER >> ./results/${dir}/time_result.txt
        echo "---------------" >> ./results/${dir}/time_result.txt
    done
done
