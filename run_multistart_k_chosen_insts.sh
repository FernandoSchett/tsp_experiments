inst=./benchmark/instances/chosen_inst/*
make clean
make 

rm benchmark/logs/*.tsp.txt

k='2'
echo "--------------- Running with k = $k" >> ./results/time_result.txt
date +"%T" >> ./results/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -i 100 -c multist_semi_nn_heur -m k_best --k=$k --seed=5 >> benchmark/logs/$inst_name.txt" 
    ./TSP -f  $i -i 100 -c multist_semi_nn_heur -m k_best --k=$k --seed=5 >> benchmark/logs/$inst_name.txt
done

date +"%T" >> ./results/time_result.txt
echo "---------------" >> ./results/time_result.txt
