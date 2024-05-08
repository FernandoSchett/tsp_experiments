#include "parameters.hpp"

void Parameters::build_path_to(){
    this->path_to = this->choice_method;
    
    if (this->stop_criterion == "iter") {
        this->path_to += "_i" + std::to_string(this->iterations);
    }
    else if (this->stop_criterion == "time") {
        this->path_to += "_time" + std::to_string(this->maxtime);
    }

    if (this->scheme == "alpha") {
        this->path_to += "_a" + std::to_string(this->alpha);
        this->path_to += "_s" + std::to_string(this->seed_rand);
    }else if (this->scheme == "k_best") {
        this->path_to += "_k" + std::to_string(this->k_best);
        this->path_to += "_s" + std::to_string(this->seed_rand);
    }else if (this->scheme == "first_improvement") {
        this->path_to += "_first_improvement";
    }else if (this->scheme == "best_improvement") {
        this->path_to += "_best_improvement"; 
    }
}