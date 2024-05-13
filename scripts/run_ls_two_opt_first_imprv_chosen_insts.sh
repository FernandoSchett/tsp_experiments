cd ..
inst=./benchmark/instances/chosen_inst/*.tsp
make clean
make 

mkdir benchmark/logs/local_search_two_opt_first_imprv
mkdir results/local_search_two_opt_first_imprv
rm benchmark/logs/local_search_two_opt_first_imprv/*.tsp.txt

echo "--------------- Running local_search" >> ./results/local_search_two_opt_first_imprv/time_result.txt
date >> ./results/local_search_two_opt_first_imprv/time_result.txt
echo $USER >> ./results/local_search_two_opt_first_imprv/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -l nn_heur_i1 -c local_search -r two_opt_first_imprv | tee -a benchmark/logs/local_search_two_opt_first_imprv/$inst_name.txt" 
    ./TSP -f  $i -l nn_heur_i1 -c local_search -r two_opt_first_imprv | tee -a benchmark/logs/local_search_two_opt_first_imprv/$inst_name.txt
done

date >> ./results/local_search_two_opt_first_imprv/time_result.txt
echo $USER >> ./results/local_search_two_opt_first_imprv/time_result.txt
echo "---------------" >> ./results/local_search_two_opt_first_imprv/time_result.txt