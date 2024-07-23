# ==============================================
# Script Name:    run_dsnn_heur_chosen_insts.sh
# Description:    Run DSNN heuristic on chosen instances and create logs and results
# Author:         Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
# Created Date:   22/07/2024
# How to run it:  bash run_dsnn_heur_chosen_insts.shs
# ==============================================

cd ..
inst=./benchmark/instances/chosen_inst/*
make clean
make 

iter=50

mkdir benchmark/logs/dsnn_heur_i${iter}
mkdir results/dsnn_heur_i${iter}

rm benchmark/logs/dsnn_heur_i${iter}/*.tsp.txt

echo "--------------- Running dsnn_heur with $iter iter" >> ./results/dsnn_heur_i${iter}/time_result.txt
date >> ./results/dsnn_heur_i${iter}/time_result.txt
echo $USER >> ./results/dsnn_heur_i${iter}/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -p iter -i $iter -c dsnn_heur >> benchmark/logs/dsnn_heur_i${iter}/$inst_name.txt" 
    ./TSP -f  $i -p iter -i $iter -c dsnn_heur >> benchmark/logs/dsnn_heur_i${iter}/$inst_name.txt
done

date >> ./results/dsnn_heur_i${iter}/time_result.txt
echo $USER >> ./results/dsnn_heur_i${iter}/time_result.txt
echo "---------------" >> ./results/dsnn_heur_i${iter}/time_result.txt
