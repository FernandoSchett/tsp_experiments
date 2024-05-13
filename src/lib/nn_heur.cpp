#include "tour.hpp"
#include "semi_greedy_schemes.hpp"

void Tour::nn_heur(IData& inst, Parameters& params) {
    std::vector<bool> visited(inst.n_nodes + 1, false);

    // Seleciona o nó inicial
    int init_node = inst.node_coords[1].id;
    this->tour.push_back(init_node);
    visited[init_node] = true;

    // Processo adaptativo de escolha do vizinho mais próximo
    while (this->tour.size() < inst.n_nodes) {
        int current_node = this->tour.back();
        int min_dist = INT_MAX;
        int chosen_node = -1;

        // Encontra vizinho mais próximo
        for (int i = 1; i <= inst.n_nodes; i++) {
            if (!visited[i] && i != current_node) {
                int dist = inst.dist(inst.node_coords[current_node], inst.node_coords[i]);
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

}

void Tour::semi_nn_heur(IData& inst, Parameters& params, std::mt19937& randmt) {
    std::vector<bool> visited(inst.n_nodes + 1, false);

    // Seleciona o nó inicial
    int init_idx = randmt() % inst.n_nodes + 1; // integer between 1 <-> inst.n_nodes
    int init_node = inst.node_coords[init_idx].id;
    this->tour.push_back(init_node);
    visited[init_node] = true;

    // Processo adaptativo de escolha do vizinho mais próximo
    std::vector<Candidate> cl;
    while (this->tour.size() < inst.n_nodes) {
        cl.clear();
        int current_node = this->tour.back();
        int min_dist = INT_MAX;
        int chosen_node = -1;

        // Coleta possíveis candidatos
        for (int i = 1; i <= inst.n_nodes; i++) {
            if (!visited[i] && i != current_node) {
                int dist = inst.dist(inst.node_coords[current_node], inst.node_coords[i]);
                Candidate c;
                c.node_orig = current_node;
                c.node = inst.node_coords[i].id;
                c.dist = dist;
                cl.push_back(c);
            }
        }
        Candidate chosen_candidate = choose_candidate(cl, params, randmt);

        // Adiciona o nó escolhido ao tour e marca como visitado
        this->tour.push_back(chosen_candidate.node);
        visited[chosen_candidate.node] = true;
    }

}