cd ..
inst=./benchmark/instances/chosen_inst/*.tsp
make clean
make 

mkdir benchmark/logs/local_search_two_opt_best_imprv_cand_list
mkdir results/local_search_two_opt_best_imprv_cand_list
rm benchmark/logs/local_search_two_opt_best_imprv_cand_list/*.tsp.txt

echo "--------------- Running local_search" >> ./results/local_search_two_opt_best_imprv_cand_list/time_result.txt
date >> ./results/local_search_two_opt_best_imprv_cand_list/time_result.txt
echo $USER >> ./results/local_search_two_opt_best_imprv_cand_list/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP2 -f  $i -l nn_heur_i1 -c local_search -r two_opt_best_imprv_cand_list | tee -a benchmark/logs/local_search_two_opt_best_imprv_cand_list/$inst_name.txt" 
    ./TSP2 -f  $i -l nn_heur_i1 -c local_search -r two_opt_best_imprv_cand_list | tee -a benchmark/logs/local_search_two_opt_best_imprv_cand_list/$inst_name.txt
done

date >> ./results/local_search_two_opt_best_imprv_cand_list/time_result.txt
echo $USER >> ./results/local_search_two_opt_best_imprv_cand_list/time_result.txt
echo "---------------" >> ./results/local_search_two_opt_best_imprv_cand_list/time_result.txt