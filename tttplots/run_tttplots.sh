#!/bin/bash

# ==============================================
# Script Name:    run_tttplots.sh
# Description:    Create and Get data from instances and run tttplots.pl for each instance
# Author:         Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
# Created Date:   22/07/2024
# ==============================================

inst="rl1304 u1060 fl1400"
alphas="prr_b_restart_100 prr_b_restart_200"
#alphas="backward forward forward_backward"
#alphas="0.05"
#alphas="0.01 0.025 0.05"

for i in $inst
do
    mkdir $i
    cd $i
    for alp in $alphas
    do
        mkdir $alp
        cd $alp
        perl ../../tttplots.pl -f ${i}_${alp}
        #touch ${i}_${alp}.dat
        cd ..
    done
    cd ..
done