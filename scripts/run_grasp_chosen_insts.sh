cd ..
inst=./benchmark/instances/chosen_inst/*
make clean
make 

time="3600"
alp="0.025000"
s=51

mkdir benchmark/logs/grasp_t${time}_a${alp}_s${s}
mkdir results/grasp_t${time}_a${alp}_s${s}

rm benchmark/logs/grasp_t${time}_a${alp}_s${s}/*.tsp.txt

echo "--------------- Running GRASP with two_opt_first_imprv_circ_search and alpha = $alp" >> ./results/grasp_t${time}_a${alp}_s${s}/time_result.txt
date >> ./results/grasp_t${time}_a${alp}_s${s}/time_result.txt
echo $USER >> ./results/grasp_t${time}_a${alp}_s${s}/time_result.txt

for i in $inst
do
    inst_name=$( basename $i ) 
    echo "./TSP -f  $i -p time -t $time -c grasp -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search >> benchmark/logs/grasp_t${time}_a${alp}_s${s}/$inst_name.txt" 
    ./TSP -f  $i -p time -t $time -c grasp -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search >> benchmark/logs/grasp_t${time}_a${alp}_s${s}/$inst_name.txt
done

date >> ./results/grasp_t${time}_a${alp}_s${s}/time_result.txt
echo $USER >> ./results/grasp_t${time}_a${alp}_s${s}/time_result.txt
echo "---------------" >> ./results/grasp_t${time}_a${alp}_s${s}/time_result.txt
