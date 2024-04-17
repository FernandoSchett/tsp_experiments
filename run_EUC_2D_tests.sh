inst=./benchmark/instances/chosen_inst/*
make clean
make 

if [ -f "output.txt" ]; then
    rm "output.txt"
fi

for i in $inst
do
    ./TSP -f  $i -c  nn_heur >> output.txt
done

for i in $inst
do
    ./TSP -f  $i -c  dsnn_heur >> output.txt  
done
