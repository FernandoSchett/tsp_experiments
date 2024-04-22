inst=./benchmark/instances/chosen_inst/*
make clean
make 

if [ -f "output.txt" ]; then
    rm "output.txt"
fi

echo "---------------" >> results/time_result.txt
date +"%T" >> results/time_result.txt



for i in $inst
do
    ./TSP -f  $i -i 100 -c multist_semi_nn_heur -m k_best --k=2 --seed=5 >> output.txt
done
