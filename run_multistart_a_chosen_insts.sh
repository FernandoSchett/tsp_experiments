inst=./benchmark/instances/chosen_inst/*
make clean
make 

if [ -f "run_multistart_a_chosen_insts.txt" ]; then
    rm "run_multistart_a_chosen_insts.txt"
fi

echo "---------------" >> results/run_multistart_a_chosen_insts.txt
date +"%T" >> results/run_multistart_a_chosen_insts.txt



for i in $inst
do
    ./TSP -f  $i -i 100 -c multist_semi_nn_heur -m alpha --alpha=0.1 --seed=5 >> run_multistart_a_chosen_insts.txt
done


date +"%T" >> results/run_multistart_a_chosen_insts.txt
echo "---------------" >> results/run_multistart_a_chosen_insts.txt
