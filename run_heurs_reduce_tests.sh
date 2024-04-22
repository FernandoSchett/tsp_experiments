inst=./benchmark/instances/reduce_tests/*
make clean
make 

if [ -f "testes_reduzidos.txt" ]; then
    rm "testes_reduzidos.txt"
fi

echo "---------------" >> results/time_result.txt
date +"%T" >> results/time_result.txt

alpha="0.1 0.2 0.3"
k="2 3 4"

for i in $inst
do
    for j in $alpha
    do
        ./TSP -f $i -c multist_semi_nn_heur -m alpha --alpha=$j --seed=5 -i 100 >> testes_reduzidos.txt
    done

    for j in $k
    do
        ./TSP -f $i -c multist_semi_nn_heur -m k_best --k=$j --seed=5 -i 100 >> testes_reduzidos.txt
    done
done