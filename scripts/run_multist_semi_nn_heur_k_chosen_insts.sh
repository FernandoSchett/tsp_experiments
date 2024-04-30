cd ..
inst=./benchmark/instances/chosen_inst/*
make clean
make 

i=100
k=2
s=5

mkdir benchmark/logs/multist_semi_nn_heur_i${iter}_k${k}_s${s}
mkdir results/multist_semi_nn_heur_i${iter}_k${k}_s${s}

rm benchmark/logs/multist_semi_nn_heur_i${iter}_k${k}_s${s}/*.tsp.txt

echo "--------------- Running with k = $k" >> ./results/multist_semi_nn_heur_i${iter}_k${k}_s${s}/time_result.txt
date >> ./results/multist_semi_nn_heur_i${iter}_k${k}_s${s}/time_result.txt
echo $USER >> ./results/multist_semi_nn_heur_i${iter}_k${k}_s${s}/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -p iter -i $iter -c multist_semi_nn_heur -m k_best --k=$k --seed=$s >> benchmark/logs/multist_semi_nn_heur_i${iter}_k${k}_s${s}/$inst_name.txt" 
    ./TSP -f  $i -p iter -i $iter -c multist_semi_nn_heur -m k_best --k=$k --seed=$s >> benchmark/logs/multist_semi_nn_heur_i${iter}_k${k}_s${s}/$inst_name.txt
done

date >> ./results/multist_semi_nn_heur_i${iter}_k${k}_s${s}/time_result.txt
echo $USER >> ./results/multist_semi_nn_heur_i${iter}_k${k}_s${s}/time_result.txt
echo "---------------" >> ./results/multist_semi_nn_heur_i${iter}_k${k}_s${s}/time_result.txt
