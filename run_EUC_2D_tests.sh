inst=./benchmark/instances/EUC_2D/*
make clean
make 

if [ -f "output.txt" ]; then
    rm "output.txt"
fi

for i in $inst
do
    ./TSP -f  $i >> output.txt  
done
