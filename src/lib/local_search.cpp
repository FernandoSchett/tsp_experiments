#include "tour.hpp"

void Tour::two_opt_first_imprv(IData& inst, Parameters& params, bool& improvement) {
    //this->print_tour();

    std::list<int>::iterator i = this->tour.begin();
    std::list<int>::iterator j = this->tour.begin(); j++;
    std::list<int>::iterator k = this->tour.begin(); k++; k++;
    std::list<int>::iterator l = this->tour.begin(); l++; l++; l++;

    //std::cout << "ELEMENTO DA FRENTE: "<< this->tour.front() << std::endl;
    this->tour.push_back(this->tour.front());

    while (l != this->tour.end()) {
        while (l != this->tour.end() && *i != *l) {
            //std::cout << "I, J,  K e L: " << *i << " " << *j << " " << *k << " " << *l << std::endl;
            int delta = inst.dist(inst.node_coords[*i], inst.node_coords[*j]) + inst.dist(inst.node_coords[*k], inst.node_coords[*l]) - inst.dist(inst.node_coords[*i], inst.node_coords[*k]) - inst.dist(inst.node_coords[*j], inst.node_coords[*l]);
            if (delta > 0) {
                improvement = true;
                //std::cout << "J e K: " << *j << " " << *k << std::endl;
                //this->print_tour();
                std::reverse(j, l);
                this->sol_value -= delta;
                //std::cout << "Improvement found: " << delta << std::endl;
                this->tour.pop_back();
                //this->calc_tour_cost(inst);
                //this->print_tour();
                return;
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

    return;
}

void Tour::two_opt_best_imprv(IData& inst, Parameters& params, bool& improvement) {
    //this->print_tour();

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

    return;
}