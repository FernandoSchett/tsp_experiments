#include "path_relinking.hpp"

Tour path_relinking(Tour& guide_tour, Tour& inicial_tour, IData& idata, Parameters& params, CPUTime& dummy_time){
    Tour inter_sol, best_tour;
    inter_sol = inicial_tour;
    best_tour = inicial_tour;

    while(!is_equal(inter_sol, guide_tour)){
        inter_sol = get_restricted_neighborhood(inter_sol, guide_tour,idata);
        if(inter_sol.sol_value < best_tour.sol_value){
           best_tour = inter_sol;
        }
    }

    local_search(best_tour,idata, params, dummy_time);
    return best_tour;
}

Tour path_relinking_mixed(Tour& guide_tour, Tour& inicial_tour, IData& idata){

}


bool is_equal(Tour& inter_sol, Tour& guide_tour){
    if(inter_sol.sol_value != guide_tour.sol_value){
        return false;
    }
    
    std::list<int>::iterator i = guide_tour.tour.begin();
    std::list<int>::iterator j = inter_sol.tour.begin();

    while(*j != *i){
        i++;
    }

    while(j != inter_sol.tour.end()){

        if(*j != *i){
            return false;
        }
        i++;

        if(i == guide_tour.tour.end()){
            i == guide_tour.tour.begin();
        }
    }
    return true;
}

Tour get_restricted_neighborhood(Tour& guide_tour, Tour& inter_sol,  IData& idata){
    Tour best_tour;
    std::list<int>::iterator i = guide_tour.tour.begin();
    std::list<int>::iterator i_prev = inter_sol.tour.begin();
    std::list<int>::iterator i_next = inter_sol.tour.begin();
    std::list<int>::iterator j = inter_sol.tour.begin();
    
    best_tour.sol_value = inter_sol.sol_value;
    int delta = 0;

    while(j != inter_sol.tour.end()){

        if(*j != *i){
            delta = idata.dist(inst.node_coords[*i] , inst.node_coords[*i]);
        }

        if(best_tour.sol_value >){
            best_tour = ;
        }
        
        i++;
        
    }
}


