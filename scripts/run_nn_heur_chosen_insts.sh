cd ..
inst=./benchmark/instances/chosen_inst/*
make clean
make 

iter=50

mkdir benchmark/logs/nn_heur_i${iter}
mkdir results/nn_heur_i${iter}

rm benchmark/logs/nn_heur_i${iter}/*.tsp.txt

echo "--------------- Running nn_heur with 50 iter" >> ./results/nn_heur_i${iter}/time_result.txt
date >> ./results/nn_heur_i${iter}/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -p iter -i $iter -c nn_heur >> benchmark/logs/nn_heur_i${iter}/$inst_name.txt" 
    ./TSP -f  $i -p iter -i $iter -c nn_heur >> benchmark/logs/nn_heur_i${iter}/$inst_name.txt
done

date >> ./results/nn_heur_i${iter}/time_result.txt
echo "---------------" >> ./results/nn_heur_i${iter}/time_result.txt
