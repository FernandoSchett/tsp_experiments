cd ..
#inst=./benchmark/instances/reduce_tests/*

inst=("brd14051.tsp" "kroA100.tsp" "rl1323.tsp")
look4=("530000" "21282" "297493") 

make clean
make 

time="300"
alphas="0.050000 0.100000 0.150000"

for alp in $alphas
do
    for s in $(seq 1 200)
    do
        dir="grasp_t${time}_a${alp}_s${s}"

        mkdir benchmark/logs/${dir}
        mkdir results/${dir}

        echo "--------------- Running reduced tests GRASP with two_opt_first_imprv_circ_search and alpha = $alp and seed = $s" >> ./results/${dir}/time_result.txt
        date >> ./results/${dir}/time_result.txt
        echo $USER >> ./results/${dir}/time_result.txt

        for i in $(seq 0 $((${#inst[@]} - 1)))
        do
            echo "./TSP -f  ${inst[$i]} -p look4 -o ${look4[$i]} -t $time -c grasp -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search >> benchmark/logs/${dir}/${inst[$i]}.txt" 
            #./TSP -f  ${inst[$i]} -p look4 -o ${look4[$i]} -t $time -c grasp -m alpha --a=$alp --seed=$s -r two_opt_first_imprv_circ_search >> benchmark/logs/${dir}/${inst[$i]}.txt
        done

        date >> ./results/${dir}/time_result.txt
        echo $USER >> ./results/${dir}/time_result.txt
        echo "---------------" >> ./results/${dir}/time_result.txt
    done
done
