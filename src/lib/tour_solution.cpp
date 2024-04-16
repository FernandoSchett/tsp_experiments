#include "tour.hpp"

void Tour::calc_tour_cost(IData& inst) {
    this->sol_value = 0;
    std::list<int>::iterator prev = this->tour.begin();
    std::list<int>::iterator curr = this->tour.begin(); curr++;
    while (curr != this->tour.end()) {
        this->sol_value += inst.dist(inst.node_coords[*prev], inst.node_coords[*curr]);
        prev++;
        curr++;
    }
    this->sol_value += inst.dist(inst.node_coords[*prev], inst.node_coords[this->tour.front()]);
}

bool Tour::is_tour_valid(IData& inst) {

    if (this->tour.size() != inst.n_nodes) {
        return false;
    }
    std::vector<int> visited(inst.n_nodes + 1, 0);
    for (int node : this->tour) {
        visited[node]++;
        if (visited[node] > 1) {
            return false;
        }
    }

    for (int i = 1; i < visited.size(); i++) {
        if (visited[i] != 1) {
            return false;
        }
    }
    return true;
}

void Tour::print_tour() {
    printf("TOUR:\n");
    for (int node : this->tour) {
        printf(" %d", node);
    }
    printf("\n");
    printf("COST = %d\n", this->sol_value);
}