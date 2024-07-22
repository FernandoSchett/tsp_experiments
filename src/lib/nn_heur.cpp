/*
 * -----------------------------------------------------------------------------
 * File Name:          nn_heur.cpp
 * Authors:            Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
 * Last Modified Date: 22/07/2024
 * Purpose: 		  Functions responsible for the Nearest Neighbor heuristic and Semi-Randomized Nearest Neighbor [3]         
 * Notes:
 * - Nearest Neighbor and Semi-Randomized Nearest Neighbor [3]
 * -----------------------------------------------------------------------------
 */

#include "tour.hpp"
#include "semi_greedy_schemes.hpp"

void Tour::nn_heur(IData& inst, Parameters& params) {
    std::vector<bool> visited(inst.n_nodes + 1, false);

    // Selects the initial node
    int init_node = inst.node_coords[1].id;
    this->tour.push_back(init_node);
    this->sol_value = 0;
    visited[init_node] = true;

    // Adaptive process for choosing the nearest neighbor
    while (this->tour.size() < inst.n_nodes) {
        int current_node = this->tour.back();
        int min_dist = INT_MAX;
        int chosen_node = -1;

        // Finds the nearest neighbor
        for (int i = 1; i <= inst.n_nodes; i++) {
            if (!visited[i] && i != current_node) {
                int dist = inst.dist(inst.node_coords[current_node], inst.node_coords[i]);
                if (dist < min_dist) {
                    min_dist = dist;
                    chosen_node = i;
                }
            }
        }

        // Adds the chosen node to the tour and marks it as visited
        this->tour.push_back(chosen_node);
        this->sol_value += min_dist;
        visited[chosen_node] = true;
    }
    this->sol_value += inst.dist(inst.node_coords[this->tour.back()], inst.node_coords[this->tour.front()]);

}

void Tour::semi_nn_heur(IData& inst, Parameters& params, std::mt19937& randmt) {
    std::vector<bool> visited(inst.n_nodes + 1, false);

    // Selects the initial node
    int init_idx = randmt() % inst.n_nodes + 1; // integer between 1 <-> inst.n_nodes
    int init_node = inst.node_coords[init_idx].id;
    this->tour.push_back(init_node);
    this->sol_value = 0;
    visited[init_node] = true;

    // Adaptive process for choosing the nearest neighbor
    std::vector<Candidate> cl;
    while (this->tour.size() < inst.n_nodes) {
        cl.clear();
        int current_node = this->tour.back();

        // Collects possible candidates
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

        // Adds the chosen node to the tour and marks it as visited
        this->tour.push_back(chosen_candidate.node);
        this->sol_value += chosen_candidate.dist;
        visited[chosen_candidate.node] = true;
    }
    this->sol_value += inst.dist(inst.node_coords[this->tour.back()], inst.node_coords[this->tour.front()]);

}
