#include "tour.hpp"

void Tour::two_opt_first_imprv(IData& inst, Parameters& params, CPUTime& cpu_time) {
    get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
    get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);

    bool improvement = true;
    while (improvement) {
        improvement = false;
        //this->print_tour();

        std::list<int>::iterator i = this->tour.begin();
        std::list<int>::iterator j = this->tour.begin(); j++;
        std::list<int>::iterator k = this->tour.begin(); k++; k++;
        std::list<int>::iterator l = this->tour.begin(); l++; l++; l++;

        //std::cout << "ELEMENTO DA FRENTE: "<< this->tour.front() << std::endl;
        this->tour.push_back(this->tour.front());

        while (!improvement && l != this->tour.end()) {
            while (!improvement && l != this->tour.end() && *i != *l) {
                // std::cout << "I, J,  K e L: " << *i << " " << *j << " " << *k << " " << *l << std::endl;
                int delta = inst.dist(inst.node_coords[*i], inst.node_coords[*j]) + inst.dist(inst.node_coords[*k], inst.node_coords[*l]) - inst.dist(inst.node_coords[*i], inst.node_coords[*k]) - inst.dist(inst.node_coords[*j], inst.node_coords[*l]);
                if (delta > 0) {
                    improvement = true;
                    //std::cout << "J e K: " << *j << " " << *k << std::endl;
                    //this->print_tour();
                    std::reverse(j, l);
                    this->sol_value -= delta;
                    //std::cout << "Improvement found: " << delta << std::endl;

                }
                k++;
                l++;
            }
            i++;
            j++;
            k = j; k++;
            l = k; l++;
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

void Tour::two_opt_best_imprv(IData& inst, Parameters& params, CPUTime& cpu_time) {
    //this->print_tour();
    get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
    get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
    bool improvement = true;
    while (improvement) {
        improvement = false;

        std::list<int>::iterator i = this->tour.begin();
        std::list<int>::iterator j = this->tour.begin(); j++;
        std::list<int>::iterator k = this->tour.begin(); k++; k++;
        std::list<int>::iterator l = this->tour.begin(); l++; l++; l++;
        std::list<int>::iterator j_best = j, l_best = l;
        int best_delta = 0;
        //std::cout << "ELEMENTO DA FRENTE: "<< this->tour.front() << std::endl;
        this->tour.push_back(this->tour.front());
        while (l != this->tour.end()) {
            while (l != this->tour.end() && *i != *l) {
                // std::cout << "I, J,  K e L: " << *i << " " << *j << " " << *k << " " << *l << std::endl;
                int delta = inst.dist(inst.node_coords[*i], inst.node_coords[*j]) + inst.dist(inst.node_coords[*k], inst.node_coords[*l]) - inst.dist(inst.node_coords[*i], inst.node_coords[*k]) - inst.dist(inst.node_coords[*j], inst.node_coords[*l]);
                if (delta > best_delta) {
                    j_best = j;
                    l_best = l;
                    best_delta = delta;
                }
                k++;
                l++;
            }
            i++;
            j++;
            k = j; k++;
            l = k; l++;
        }

        if (best_delta > 0) {
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

void Tour::two_opt_best_imprv_cand_list(IData& inst, Parameters& params, CPUTime& cpu_time) {

}

void Tour::two_opt_first_imprv_circ_search(IData& inst, Parameters& params, CPUTime& cpu_time) {

}
