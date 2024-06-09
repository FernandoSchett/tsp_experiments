#include "path_relinking.hpp"

Tour path_relinking(Tour& guide_tour, Tour& inicial_tour, IData& idata, Parameters& params, CPUTime& dummy_time){
    Tour inter_sol, best_tour;
    inter_sol = inicial_tour;
    best_tour = inicial_tour;
    bool updated = false;
    //std::cout << "SOCORRO SOCORRO: " <<'\n';
    if(neighborhood_size(inter_sol, guide_tour) < 4 ){
        return best_tour;
    }
    do{
        //std::cout << "SOCORRO2 SOCORRO2: " <<'\n';

        inter_sol = get_best_neighbor(guide_tour, inter_sol, idata);
        // std::cout << "AQUI GUIDE_depois: " <<'\n';
        // guide_tour.print_tour();
        // std::cout << "AQUI INTERSOL_depois: " <<'\n';
        // inter_sol.print_tour();
        // std::cout <<"\n";
        if(inter_sol.sol_value < best_tour.sol_value){
            std::cout << "ENTROU AQUI" <<'\n';
            updated = true;
            best_tour = inter_sol;
        }
        //std::cout << "BEST: " << best_tour.sol_value <<'\n';

    }while(neighborhood_size(inter_sol, guide_tour) >= 2);

    

    if(updated){
        local_search(best_tour, idata, params, dummy_time);
    }

    return best_tour;
}

Tour path_relinking_mixed(Tour& guide_tour, Tour& inicial_tour, IData& idata, Parameters &params, CPUTime &dummy_time){
    Tour inter_sol, best_tour, aux;
    inter_sol = inicial_tour;
    best_tour = inicial_tour;
    
    bool updated = false;
    //std::cout << "SOCORRO SOCORRO: " <<'\n';
    if(neighborhood_size(inter_sol, guide_tour) < 4 ){
        return best_tour;
    }
    do{
        //std::cout << "SOCORRO2 SOCORRO2: " <<'\n';

        inter_sol = get_best_neighbor(guide_tour, inter_sol, idata);
        // std::cout << "AQUI GUIDE_depois: " <<'\n';
        // guide_tour.print_tour();
        // std::cout << "AQUI INTERSOL_depois: " <<'\n';
        // inter_sol.print_tour();
        // std::cout <<"\n";


        // std::cout << inter_sol.sol_value <<'\n';
        // std::cout << guide_tour.sol_value <<'\n';
        // inter_sol.calc_tour_cost(idata);
        // guide_tour.calc_tour_cost(idata);
        // std::cout << inter_sol.sol_value <<'\n';
        // std::cout << guide_tour.sol_value <<'\n' <<'\n'<<'\n';

        if(inter_sol.sol_value < best_tour.sol_value){
            std::cout << "ENTROU AQUI" <<'\n';
            updated = true;
            best_tour = inter_sol;
        }
        aux = guide_tour;
        guide_tour = inter_sol;
        inter_sol = aux;
        //std::cout << "BEST: " << best_tour.sol_value <<'\n';

    }while(neighborhood_size(inter_sol, guide_tour) >= 2);

    if(updated){
        local_search(best_tour, idata, params, dummy_time);
    }

    return best_tour;
}


int neighborhood_size(Tour& inter_sol, Tour& guide_tour){
    
    int neighbors = 0; 
    std::list<int>::iterator i = guide_tour.tour.begin();
    std::list<int>::iterator j = inter_sol.tour.begin();
    
    while(*j != *i){
        j++;
    }

    while(i != guide_tour.tour.end()){

        //std::cout << "J: " << *j <<'\n';
        //std::cout << "I: " <<  *i <<'\n';
        //std::cout << '\n';
        if(*j != *i){
            neighbors++;
            //std::cout << "TROCOU:" << neighbors <<'\n';
            //std::cout << *i <<'\n';
            //std::cout << *j <<'\n';
        }
        
        i++;
        j++;
        if(j == inter_sol.tour.end()){
            //std::cout << "ENTROU AQUI" <<'\n';
            j = inter_sol.tour.begin();
        }
    }
    //std::cout << "NEIGHBORS: " << neighbors <<'\n';
    //guide_tour.print_tour();
    //inter_sol.print_tour();
    return neighbors;
}

Tour get_best_neighbor(Tour& guide_tour, Tour& inter_sol,  IData& inst){
    //std::cout << "COMECOU A PROCURAR " <<'\n';
    Tour best_tour = inter_sol;
    std::list<int>::iterator i = guide_tour.tour.begin();
    std::list<int>::iterator j = best_tour.tour.begin();
    std::list<int>::iterator aux, best_j, best_aux;
    Point p_j, np_j, pp_j, p_aux, np_aux, pp_aux;
    //std::cout << "SOCORRO3 SOCORRO3: " <<'\n';
    
    int best_delta = INT_MIN, delta,  d_removed, d_added;

    while(j != best_tour.tour.end()){
        //std::cout << "SOCORRO4 SOCORRO4: " <<'\n';
        if(*j != *i){
            //std::cout << "ENTROU " << *j <<'\n';
            aux = j;
            while(*aux != *i){
                aux++;
                if(aux == best_tour.tour.end()){
                    aux = best_tour.tour.begin();
                }
                //std::cout << "SOCORRO5 SOCORRO5: " <<'\n';
            }
            //std::cout << "SOCORRO6 SOCORRO6: " <<'\n';
            p_j = inst.node_coords[*j];
            if(std::next(j) != best_tour.tour.end()){
                np_j = inst.node_coords[*std::next(j)];
            }else{
                np_j = inst.node_coords[best_tour.tour.front()];    
            }
            if(j != best_tour.tour.begin()){
                pp_j= inst.node_coords[*std::prev(j)];
            }else{
                pp_j = inst.node_coords[best_tour.tour.back()];
            }

            p_aux = inst.node_coords[*aux];
            if(std::next(aux) != best_tour.tour.end()){
                np_aux = inst.node_coords[*std::next(aux)];
            }else{
                np_aux = inst.node_coords[best_tour.tour.front()];
            }
            if(aux != best_tour.tour.begin()){
                pp_aux= inst.node_coords[*std::prev(aux)];
            }else{
                pp_aux = inst.node_coords[best_tour.tour.back()];
            }
            
            
            d_removed = inst.dist(pp_j, p_j) + inst.dist(p_j, np_j) + inst.dist(p_aux, pp_aux) + inst.dist(p_aux, np_aux);
            d_added = inst.dist(pp_j, p_aux) + inst.dist(p_aux, np_j) + inst.dist(p_j, pp_aux) + inst.dist(np_aux, p_j);
            

            delta = d_removed - d_added;
            if( best_delta < delta){
                // std::cout << "MELHOR DELTA " << best_delta <<'\n';
                // std::cout << "DELTA " << delta <<'\n';
                // std::cout << "ELEMENTO " << *aux <<'\n';
                // std::cout << "ELEMENTO " << *j <<'\n';
                // std::cout << "ELEMENTO " << *i <<'\n';
                // std::cout << "\n";

                // std::cout << inst.dist(pp_j, p_j) <<'\n';
                // std::cout << inst.dist(p_j, np_j) <<'\n';
                // std::cout << inst.dist(p_aux, pp_aux) <<'\n';
                // std::cout << inst.dist(p_aux, np_aux) <<'\n';
                // std::cout << inst.dist(pp_j, p_aux) <<'\n';
                // std::cout << inst.dist(p_aux, np_j) <<'\n';
                // std::cout << inst.dist(p_j, pp_aux) <<'\n';
                // std::cout << inst.dist(np_aux, p_j) <<'\n';
                // std::cout << "DELTA REMOVED: " << d_removed <<'\n';
                // std::cout << "DELTA ADDED: " << d_added <<'\n';
                // std::cout << "iteradores:" <<'\n';
                // std::cout << pp_j.id <<'\n';
                // std::cout << p_j.id <<'\n';
                // std::cout << np_j.id <<'\n';
                // std::cout << pp_aux.id <<'\n';
                // std::cout << p_aux.id <<'\n';
                // std::cout << np_aux.id <<'\n';
                // std::cout << "AQUI MELHOR VIZINHO SWAP: " <<'\n';
                // best_tour.print_tour(); 

                best_delta = delta;
                best_j = j;
                best_aux = aux;
            }
        }

        //std::cout << "VALOR DE I:" << *i <<'\n';
        //std::cout << "VALOR DE J:" << *j <<'\n';
        /*
        std::cout << "guide_tour:";
        guide_tour.print_tour(); 
        std::cout << "inter_sol:";
        inter_sol.print_tour();
        std::cout << "best_tour:";
        best_tour.print_tour();
        */
        j++;
        i++;
    }
    //std::cout << "SOCORRO10 SOCORRO10: " <<'\n';  

    //std::cout << "TROCAR 1:" <<  *best_j <<'\n';
    //std::cout << "TROCAR 2:" << *best_aux <<'\n';
    // std::cout << "DELTA:" << best_delta <<'\n';

    // std::cout << "AQUI MELHOR VIZINHO SEM TROCAR: " <<'\n';
    // best_tour.print_tour();
    
    std::iter_swap(best_j, best_aux);
    best_tour.sol_value -= best_delta;
    // std::cout << "AQUI MELHOR VIZINHO SWAP COM DELTA VALOR ATUALIZADO: " <<'\n';
    // best_tour.print_tour();
    // best_tour.calc_tour_cost(inst);


    // std::cout << "AQUI GUIDE: " <<'\n';
    // guide_tour.print_tour();
    // std::cout << "AQUI INTERSOL: " <<'\n';
    // inter_sol.print_tour();
    // std::cout << "AQUI MELHOR VIZINHO SWAP: " <<'\n';
    // best_tour.print_tour();    
    // std::cout << "TERMINOU INF " <<'\n';

    return best_tour;
}


