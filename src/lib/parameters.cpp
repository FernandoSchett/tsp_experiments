/*
 * -----------------------------------------------------------------------------
 * File Name:          parameters.cpp
 * Authors:            Vitor Barbosa
 * Last Modified Date: 22/07/2024
 * Purpose: 		  Functions responsible for setting the path to the output file.
 * Notes:
 * - choice_method+stop_criterion+scheme+local_search         
 * -----------------------------------------------------------------------------
 */


#include "parameters.hpp"
#include <iostream>

void Parameters::build_path_to(){
    this->path_to = this->choice_method;
    if(this->choice_method == "grasp_pr" || this->choice_method == "grasp_prr"){
        this->path_to += "_" + this->pr_mode;
    }
    
    if (this->stop_criterion == "iter") {
        this->path_to += "_i" + std::to_string(this->iterations);
    }
    else if (this->stop_criterion == "time" || this->stop_criterion == "look4") {
        this->path_to += "_t" + std::to_string(this->maxtime);
    }

    if (this->scheme == "alpha") {
        this->path_to += "_a" + std::to_string(this->alpha);
        this->path_to += "_s" + std::to_string(this->seed_rand);
    }else if (this->scheme == "k_best") {
        this->path_to += "_k" + std::to_string(this->k_best);
        this->path_to += "_s" + std::to_string(this->seed_rand);
    }
    
    if (this->choice_method == "local_search") {
        this->path_to += "_" + this->local_search;
    }

    std::cout << "path_to: " << this->path_to << std::endl;
    
}   