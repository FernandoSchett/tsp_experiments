#include "tour.hpp"

void Tour::two_opt_first_imprv(IData& inst, Parameters& params, CPUTime& cpu_time)
{
    get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
    get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);

    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        // this->print_tour();

        std::list<int>::iterator i = this->tour.begin();
        std::list<int>::iterator j = this->tour.begin();
        j++;
        std::list<int>::iterator k = this->tour.begin();
        k++;
        k++;
        std::list<int>::iterator l = this->tour.begin();
        l++;
        l++;
        l++;

        // std::cout << "ELEMENTO DA FRENTE: "<< this->tour.front() << std::endl;
        this->tour.push_back(this->tour.front());

        while (!improvement && l != this->tour.end())
        {
            while (!improvement && l != this->tour.end() && *i != *l)
            {
                // std::cout << "I, J,  K e L: " << *i << " " << *j << " " << *k << " " << *l << std::endl;
                int delta = inst.dist(inst.node_coords[*i], inst.node_coords[*j]) + inst.dist(inst.node_coords[*k], inst.node_coords[*l]) - inst.dist(inst.node_coords[*i], inst.node_coords[*k]) - inst.dist(inst.node_coords[*j], inst.node_coords[*l]);
                if (delta > 0)
                {
                    improvement = true;
                    // std::cout << "J e K: " << *j << " " << *k << std::endl;
                    // this->print_tour();
                    std::reverse(j, l);
                    this->sol_value -= delta;
                    // std::cout << "Improvement found: " << delta << std::endl;
                }
                k++;
                l++;
            }
            i++;
            j++;
            k = j;
            k++;
            l = k;
            l++;
        }

        this->tour.pop_back();
        // this->calc_tour_cost(inst);
        // this->print_tour();
        std::cout << "COST = " << this->sol_value << std::endl;
        get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
    }

    get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
    cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);

    return;
}

void Tour::two_opt_best_imprv(IData& inst, Parameters& params, CPUTime& cpu_time)
{
    // this->print_tour();
    get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
    get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
    bool improvement = true;

    while (improvement)
    {
        improvement = false;

        std::list<int>::iterator i = this->tour.begin();
        std::list<int>::iterator j = this->tour.begin();
        j++;
        std::list<int>::iterator k = this->tour.begin();
        k++;
        k++;
        std::list<int>::iterator l = this->tour.begin();
        l++;
        l++;
        l++;
        std::list<int>::iterator j_best = j, l_best = l;
        int best_delta = 0;
        // std::cout << "ELEMENTO DA FRENTE: "<< this->tour.front() << std::endl;
        this->tour.push_back(this->tour.front());
        while (l != this->tour.end())
        {
            while (l != this->tour.end() && *i != *l)
            {
                // std::cout << "I, J,  K e L: " << *i << " " << *j << " " << *k << " " << *l << std::endl;
                int delta = inst.dist(inst.node_coords[*i], inst.node_coords[*j]) + inst.dist(inst.node_coords[*k], inst.node_coords[*l]) - inst.dist(inst.node_coords[*i], inst.node_coords[*k]) - inst.dist(inst.node_coords[*j], inst.node_coords[*l]);
                if (delta > best_delta)
                {
                    j_best = j;
                    l_best = l;
                    best_delta = delta;
                }
                k++;
                l++;
            }
            i++;
            j++;
            k = j;
            k++;
            l = k;
            l++;
        }

        if (best_delta > 0)
        {
            improvement = true;
            std::reverse(j_best, l_best);
            this->sol_value -= best_delta;
        }
        this->tour.pop_back();

        std::cout << "COST = " << this->sol_value << "\n";
        get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
    }

    get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
    cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);

    return;
}

void Tour::two_opt_best_imprv_cand_list(IData& inst, Parameters& params, CPUTime& cpu_time)
{
    //this->print_tour();
    get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
    get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);

    std::list<Candidate_ls> candidate_list;
    Candidate_ls candidate;
    this->tour.push_back(this->tour.front());
    candidate_list = get_candidate_list(inst);
    while(!candidate_list.empty()){
        
        auto cmp = [](const Candidate_ls& a, const Candidate_ls& b) { return a.delta > b.delta; };
        candidate_list.sort(cmp);
        // this->print_tour();

        /*
        std::cout << "TAM DA LISTA: " << candidate_list.size() << std::endl;
        for (Candidate_ls c : candidate_list){
            std::cout << "DELTA = " << c.delta << " I = " << *c.i << " J = " << *c.j << " K = " << *c.k << " L = " << *c.l << std::endl;
        }
        */

        candidate = candidate_list.front();
        std::reverse(candidate.j, candidate.l);
        this->sol_value -= candidate.delta;
        candidate_list.pop_front();
        //std::cout << "TROCA DELTA = " << candidate.delta << " I = " << candidate.val_i << " J = " << candidate.val_j << " K = " << candidate.val_k << " L = " << candidate.val_l << std::endl;
        //this->print_tour();

        while (!candidate_list.empty())
        {
            candidate = candidate_list.front();
            //std::cout << *candidate.j << " " << *candidate.i << " " << *candidate.k << " " << *candidate.l << std::endl; 
            //std::cout << candidate.val_j << " " << candidate.val_i << " " << candidate.val_k << " " << candidate.val_l << std::endl; 

            if (*candidate.i != candidate.val_i 
                || *candidate.j != candidate.val_j 
                || *candidate.k != candidate.val_k 
                || *candidate.l != candidate.val_l){
                candidate_list.pop_front();
                continue;
            }


            int delta = inst.dist(inst.node_coords[*candidate.i], inst.node_coords[*candidate.j]) + inst.dist(inst.node_coords[*candidate.k], inst.node_coords[*candidate.l]) - inst.dist(inst.node_coords[*candidate.i], inst.node_coords[*candidate.k]) - inst.dist(inst.node_coords[*candidate.j], inst.node_coords[*candidate.l]);
            candidate = candidate_list.front();
            std::reverse(candidate.j, candidate.l);
            this->sol_value -= delta;
            candidate_list.pop_front();

            //std::cout << "TROCA DELTA = " << delta << " I = " << candidate.val_i << " J = " << candidate.val_j << " K = " << candidate.val_k << " L = " << candidate.val_l << std::endl;
            //this->print_tour();
            //this->calc_tour_cost(inst);
            //this->print_tour();
        }

        candidate_list = get_candidate_list(inst);
        
        //this->tour.pop_back();
        //this->print_tour();
        //std::cout << "TOUR VALID: " << this->is_tour_valid(inst) << std::endl;
        //this->tour.push_back(this->tour.front());
        //exit(0);
        
    }

    this->tour.pop_back();
    //std::cout << "COST = " << this->sol_value << "\n";
    get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);

    get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
    cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);

    return;
    
}

void Tour::two_opt_first_imprv_circ_search(IData& inst, Parameters& params, CPUTime& cpu_time){
    get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
    get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
    
     
    std::pair<std::list<int>::iterator,std::list<int>::iterator> closest_neighbor;
    closest_neighbor.first = this->tour.begin();
    closest_neighbor.second = this->tour.begin(); closest_neighbor.second++; closest_neighbor.second++;

    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        // this->print_tour();

        // std::cout << "ELEMENTO DA FRENTE: "<< this->tour.front() << std::endl;
        this->tour.push_back(this->tour.front());

        closest_neighbor = search_neighbors(inst, improvement, closest_neighbor.first , closest_neighbor.second);
        std::cout << *closest_neighbor.first << " " << *closest_neighbor.second  << std::endl;


        this->tour.pop_back();
        // this->calc_tour_cost(inst);
        // this->print_tour();
        std::cout << "COST = " << this->sol_value << std::endl;
        get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
    }

    get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
    cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);

    return;
}

std::pair<std::list<int>::iterator,std::list<int>::iterator> Tour::search_neighbors(IData& inst, bool& improvement, std::list<int>::iterator& init_i, std::list<int>::iterator& init_k){

    std::list<int>::iterator i = init_i;
    std::list<int>::iterator end_i = init_i;

    std::list<int>::iterator j = i; j++;

    std::list<int>::iterator k = init_k;
    std::list<int>::iterator end_k = init_k; 

    std::list<int>::iterator l = k; l++;
    
    while (end_k){
        while (l != this->tour.end() && *i != *l){
            int delta = inst.dist(inst.node_coords[*i], inst.node_coords[*j]) + inst.dist(inst.node_coords[*k], inst.node_coords[*l]) - inst.dist(inst.node_coords[*i], inst.node_coords[*k]) - inst.dist(inst.node_coords[*j], inst.node_coords[*l]);
            if (delta > 0)
            // std::cout << "I, J,  K e L: " << *i << " " << *j << " " << *k << " " << *l << std::endl;
            {
                improvement = true;
                // this->print_tour();
                std::cout << *i << " " << *j << " " << *k << " " << *l << std::endl; 
                std::reverse(j, l);
                std::cout << *i << " " << *j << " " << *k << " " << *l << std::endl; 
                //std::cout << "J e K: " << *j << " " << *k << std::endl;
                this->sol_value -= delta;
                return make_pair(i, j);
                // std::cout << "Improvement found: " << delta << std::endl;
            }
            k++;
            l++;
        }
        i++;
        j++;
        k = j;
        k++;
        l = k;
        l++;
        if(l != this->tour.end()){
            i = this->tour.begin();
            j = i; j++;
            k = j; k++;
            l = k; l++;
        }
    }
    return make_pair(this->tour.begin(), this->tour.begin()++++);
}

std::list<Candidate_ls> Tour::get_candidate_list(IData& inst){

    std::list<int>::iterator i = this->tour.begin();
    std::list<int>::iterator j = this->tour.begin(); j++;
    std::list<int>::iterator k = this->tour.begin(); k++; k++;
    std::list<int>::iterator l = this->tour.begin(); l++; l++; l++;

    std::list<Candidate_ls> candidate_list;
    Candidate_ls candidate;

    // std::cout << "ELEMENTO DA FRENTE: "<< this->tour.front() << std::endl;
    while (l != this->tour.end())
    {
        while (l != this->tour.end() && *i != *l)
        {
            // std::cout << "I, J,  K e L: " << *i << " " << *j << " " << *k << " " << *l << std::endl;

            int delta = inst.dist(inst.node_coords[*i], inst.node_coords[*j]) + inst.dist(inst.node_coords[*k], inst.node_coords[*l]) - inst.dist(inst.node_coords[*i], inst.node_coords[*k]) - inst.dist(inst.node_coords[*j], inst.node_coords[*l]);
            if (delta > 0)
            {
                candidate.delta = delta;
                candidate.j = j;
                candidate.l = l;
                candidate.k = k;
                candidate.i = i;
                candidate.val_i = *i;
                candidate.val_j = *j;
                candidate.val_k = *k;
                candidate.val_l = *l;
                candidate_list.push_back(candidate);

            }
            k++;
            l++;
        }

        i++;
        j++;
        k = j;
        k++;
        l = k;
        l++;
    }
    return candidate_list;
}

