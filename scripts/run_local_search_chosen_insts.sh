cd ..
inst=./benchmark/instances/chosen_inst/*.tsp
make clean
make 

iter=50

mkdir benchmark/logs/local_search_best_improvement
mkdir benchmark/logs/local_search_first_improvement

mkdir results/local_search_best_improvement
mkdir results/local_search_first_improvement

rm benchmark/logs/local_search_best_improvement/*.tsp.txt
rm benchmark/logs/local_search_first_improvement/*.tsp.txt

echo "--------------- Running local_search" >> ./results/local_search_best_improvement/time_result.txt
date >> ./results/local_search_best_improvement/time_result.txt
echo $USER >> ./results/local_search_best_improvement/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -l nn_heur_i1 -c local_search -m best_improvement >> benchmark/logs/local_search_best_improvement/$inst_name.txt" 
    ./TSP -f  $i -l nn_heur_i1 -c local_search -m best_improvement >> benchmark/logs/local_search_best_improvement/$inst_name.txt
done

date >> ./results/local_search_best_improvement/time_result.txt
echo $USER >> ./results/local_search_best_improvement/time_result.txt
echo "---------------" >> ./results/local_search_best_improvement/time_result.txt


echo "--------------- Running local_search" >> ./results/local_search_first_improvement/time_result.txt
date >> ./results/local_search_first_improvement/time_result.txt
echo $USER >> ./results/local_search_first_improvement/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -l nn_heur_i1 -c local_search -m first_improvement >> benchmark/logs/local_search_first_improvement/$inst_name.txt" 
    ./TSP -f  $i -l nn_heur_i1 -c local_search -m first_improvement >> benchmark/logs/local_search_first_improvement/$inst_name.txt
done

date >> ./results/local_search_first_improvement/time_result.txt
echo $USER >> ./results/local_search_first_improvement/time_result.txt
echo "---------------" >> ./results/local_search_first_improvement/time_result.txt
