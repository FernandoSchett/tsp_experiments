cd ..
inst=./benchmark/instances/chosen_inst/*
make clean
make 

iter=50

mkdir benchmark/logs/dsnn_heur_i${iter}
mkdir results/dsnn_heur_i${iter}

rm benchmark/logs/dsnn_heur_i${iter}/*.tsp.txt

echo "--------------- Running dsnn_heur with 50 iter" >> ./results/dsnn_heur_i${iter}/time_result.txt
date >> ./results/dsnn_heur_i${iter}/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -p iter -i $iter -c dsnn_heur >> benchmark/logs/dsnn_heur_i${iter}/$inst_name.txt" 
    ./TSP -f  $i -p iter -i $iter -c dsnn_heur >> benchmark/logs/dsnn_heur_i${iter}/$inst_name.txt
done

date >> ./results/dsnn_heur_i${iter}/time_result.txt
echo "---------------" >> ./results/dsnn_heur_i${iter}/time_result.txt
