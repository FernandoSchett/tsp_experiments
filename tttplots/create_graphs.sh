#!/bin/bash

inst="kroA100 si1032 st70"
alphas="0.01 0.025 0.05 0.1"

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
    
    for alp in $alphas
    do  
        echo -n \"../${alp}/${i}_${alp}-ee.dat\" t \"${alp} empirical\" w points, \"../${alp}/${i}_${alp}-te.dat\" t \"${alp} theoretical\" w lines lt 3, >> ${dir}          
    done
    
    cd inst_data
    gnuplot plot_ttt_alphas.gpl
    cd ..
    cd ..
done