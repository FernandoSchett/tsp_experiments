#include "tour.hpp"

void Tour::nn_heur(IData& inst, Parameters& params) {
    std::vector<bool> visited(inst.n_nodes + 1, false);

    // Seleciona o nó inicial
    int init_node = inst.node_coords[1].id;
    this->tour.push_back(init_node);
    visited[init_node] = true;

    // Processo adaptativo de escolha do vizinho mais próximo
    while (this->tour.size() < inst.n_nodes) {
        int current_node = this->tour.back();
        int min_dist = 1000000;
        int chosen_node = -1;

        // Coleta possíveis candidatos
        for (int i = 1; i <= inst.n_nodes; i++) {
            if (!visited[i] && i != current_node) {
                int dist = inst.distances[current_node][i];
                if (dist < min_dist) {
                    min_dist = dist;
                    chosen_node = i;
                }
            }
        }

        // Adiciona o nó escolhido ao tour e marca como visitado
        this->tour.push_back(chosen_node);
        visited[chosen_node] = true;
    }
    
    this->sol_value = 0;
    std::list<int>::iterator prev = this->tour.begin();
    std::list<int>::iterator curr = this->tour.begin(); curr++;
    while (curr != this->tour.end()) {
        this->sol_value += inst.distances[*prev][*curr];
        prev++;
        curr++;
    }
    this->sol_value += inst.distances[*prev][this->tour.front()];

}
