#!/bin/bash

cd ..
inst=("kroA100.tsp" "si1032.tsp")
look4=("21282" "92650") 
time="600"
alphas="0.010000 0.025000 0.050000 0.100000"

make clean
make 

for alp in $alphas
do
    for s in $(seq 1 50)
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
