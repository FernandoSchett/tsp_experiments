#include "parameters.hpp"

void Parameters::build_path_to(){
    this->path_to = this->choice_method;
    
    if (this->stop_criterion == "iter") {
        this->path_to += "_i" + std::to_string(this->iterations);
    }
    else if (this->stop_criterion == "time") {
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
}