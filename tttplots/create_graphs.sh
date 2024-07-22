#!/bin/bash

#inst="kroA100 si1032 st70"
#alphas="0.01 0.025 0.05 0.1"
#inst="brd14051 d15112.tsp d18512.tsp"
#alphas="0.01 0.025 0.05"
inst="rl1304 u1060 fl1400"
#alphas=("0.05" "backward" "forward" "forward_backward")
#nomes=("0.05" "backward" "forward" "backward-forward")
alphas=("backward" "prr_b_restart_100" "prr_b_restart_200")
nomes=("backward" "restart-100" "restart-200")

#alphas="0.05"

dir=inst_data/plot_ttt_alphas.gpl

for i in $inst
do
    cd $i
    mkdir inst_data

    echo set xlabel \'time to target solution\' > ${dir}
    echo set size ratio 1 >> ${dir} 
    echo set ylabel \'cumulative probability\' >> ${dir}
    echo set yrange [0:1] >> ${dir} 
    echo set key right bottom >> ${dir}
    echo set grid >> ${dir}
    echo set title \'${i}\' >> ${dir}
    echo set terminal postscript color \'Helvetica\' >> ${dir} 
    echo set output \'${i}_ttt.ps\' >> ${dir} 
    echo -n "plot " >> ${dir} 
    
    for j in $(seq 0 $((${#alphas[@]} - 1)))
    do  
        echo -n \"../${alphas[$j]}/${i}_${alphas[$j]}-ee.dat\" t \"${nomes[$j]} empirical\" w points, \"../${alphas[$j]}/${i}_${alphas[$j]}-te.dat\" t \"${nomes[$j]} theoretical\" w lines lt 3, >> ${dir}          
    done
    
    cd inst_data
    gnuplot plot_ttt_alphas.gpl
    cd ..
    cd ..
done