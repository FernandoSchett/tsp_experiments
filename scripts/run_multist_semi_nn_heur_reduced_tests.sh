# ==============================================
# Script Name:    run_multist_semi_nn_heur_reduced_tests.sh
# Description:    Run SEMI-NN (alpha scheme) heuristic on reduced instances and create logs and results
# Author:         Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
# Created Date:   22/07/2024
# ==============================================

cd ..
inst=./benchmark/instances/reduce_tests/*
make clean
make 

if [ -f "testes_reduzidos.txt" ]; then
    rm "testes_reduzidos.txt"
fi

echo "---------------" >> results/testes_reduzidos.txt
date >> results/testes_reduzidos.txt
echo $USER >> results/testes_reduzidos.txt

alpha="0.1 0.2 0.3"
k="2 3 4"

for i in $inst
do
    for j in $alpha
    do
        echo "./TSP -f $i -c multist_semi_nn_heur -m alpha --alpha=$j --seed=5 -i 100 >> testes_reduzidos.txt"
        ./TSP -f $i -c multist_semi_nn_heur -m alpha --alpha=$j --seed=5 -i 100 >> testes_reduzidos.txt
         
    done

    for j in $k
    do
        echo "./TSP -f $i -c multist_semi_nn_heur -m k_best --k=$j --seed=5 -i 100 >> testes_reduzidos.txt"
        ./TSP -f $i -c multist_semi_nn_heur -m k_best --k=$j --seed=5 -i 100 >> testes_reduzidos.txt
    done
done

date >> results/testes_reduzidos.txt
echo $USER >> results/testes_reduzidos.txt
echo "---------------" >> results/testes_reduzidos.txt