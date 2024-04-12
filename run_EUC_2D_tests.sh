inst=./benchmark/instances/EUC_2D/*
make clean
make 

for i in $inst
do
    ./TSP -f  $i >> output.txt  
done
