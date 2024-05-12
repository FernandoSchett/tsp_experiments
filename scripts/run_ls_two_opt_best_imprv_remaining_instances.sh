cd ..

inst="./benchmark/instances/chosen_inst/rl1304.tsp ./benchmark/instances/chosen_inst/rl1323.tsp ./benchmark/instances/chosen_inst/rl11849.tsp ./benchmark/instances/chosen_inst/si1032.tsp ./benchmark/instances/chosen_inst/st70.tsp ./benchmark/instances/chosen_inst/u1060.tsp ./benchmark/instances/chosen_inst/vm1084.tsp"
make clean
make 

mkdir benchmark/logs/local_search_two_opt_best_imprv
mkdir results/local_search_two_opt_best_imprv
# rm benchmark/logs/local_search_two_opt_best_imprv/*.tsp.txt

echo "--------------- Running local_search" >> ./results/local_search_two_opt_best_imprv/time_result.txt
date >> ./results/local_search_two_opt_best_imprv/time_result.txt
echo $USER >> ./results/local_search_two_opt_best_imprv/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -l nn_heur_i1 -c local_search -r two_opt_best_imprv | tee -a benchmark/logs/local_search_two_opt_best_imprv/$inst_name.txt" 
    ./TSP -f  $i -l nn_heur_i1 -c local_search -r two_opt_best_imprv | tee -a benchmark/logs/local_search_two_opt_best_imprv/$inst_name.txt
done

date >> ./results/local_search_two_opt_best_imprv/time_result.txt
echo $USER >> ./results/local_search_two_opt_best_imprv/time_result.txt
echo "---------------" >> ./results/local_search_two_opt_best_imprv/time_result.txt