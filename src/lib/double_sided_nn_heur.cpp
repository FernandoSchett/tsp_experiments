#include "tour.hpp"
#include "semi_greedy_schemes.hpp"

void Tour::double_sided_nn_heur(IData& inst, Parameters& params) {
    std::vector<bool> visited(inst.n_nodes + 1, false);

    // Initial node
    int init_node = inst.node_coords[1].id;
    this->tour.push_back(init_node);
    visited[init_node] = true;

    // Insert nearest node to initial node
    int nrst_node = 0;
    int nrst_dist = 0;
    for (int i = 1; i < inst.node_coords.size(); i++) {
        int dist = inst.dist(inst.node_coords[init_node], inst.node_coords[i]);
        if (i != init_node && (nrst_node == 0 || (!visited[i] && dist < nrst_dist))) {
            nrst_node = i;
            nrst_dist = dist;
        }
    }
    this->tour.push_back(nrst_node);
    visited[nrst_node] = true;

    // Keep inserting nearest node of any of the two open extremities
    while (this->tour.size() < inst.n_nodes) {
        int nrst_node_left = 0;
        int nrst_dist_left = 0;
        for (int i = 1; i < inst.node_coords.size(); i++) {
            int dist = inst.dist(inst.node_coords[tour.front()], inst.node_coords[i]);
            if (i != tour.front() && ((!visited[i] && nrst_node_left == 0) || (!visited[i] && dist < nrst_dist_left))) {
                nrst_node_left = i;
                nrst_dist_left = dist;
            }
        }

        int nrst_node_right = 0;
        int nrst_dist_right = 0;
        for (int i = 1; i < inst.node_coords.size(); i++) {
            int dist = inst.dist(inst.node_coords[tour.back()], inst.node_coords[i]);
            if (i != tour.back() && ((!visited[i] && nrst_node_right == 0) || (!visited[i] && dist < nrst_dist_right))) {
                nrst_node_right = i;
                nrst_dist_right = dist;
            }
        }

        if (nrst_dist_left < nrst_dist_right) {
            this->tour.push_front(nrst_node_left);
            visited[nrst_node_left] = true;
        }
        else {
            this->tour.push_back(nrst_node_right);
            visited[nrst_node_right] = true;
        }
    }

}

void Tour::semi_double_sided_nn_heur(IData& inst, Parameters& params, std::mt19937& randmt) {
    std::vector<bool> visited(inst.n_nodes + 1, false);

    // Initial node
    int init_idx = randmt() % inst.n_nodes + 1; // integer between 1 <-> inst.n_nodes
    int init_node = inst.node_coords[init_idx].id;
    this->tour.push_back(init_node);
    visited[init_node] = true;

    // Insert nearest node to initial node
    std::vector<Candidate> cl;
    for (int i = 1; i < inst.node_coords.size(); i++) {
        int dist = inst.dist(inst.node_coords[init_node], inst.node_coords[i]);
        if (i != init_node && !visited[i]) {
            Candidate c;
            c.node_orig = inst.node_coords[init_node].id;
            c.node = inst.node_coords[i].id;
            c.dist = dist;
            cl.push_back(c);
        }
    }
    Candidate chosen_candidate = choose_candidate(cl, params, randmt);
    this->tour.push_back(chosen_candidate.node);
    visited[chosen_candidate.node] = true;

    // Keep inserting nearest node of any of the two open extremities
    while (this->tour.size() < inst.n_nodes) {
        cl.clear();
        for (int i = 1; i < inst.node_coords.size(); i++) {
            int dist = inst.dist(inst.node_coords[tour.front()], inst.node_coords[i]);
            if (i != tour.front() && !visited[i]) {
                Candidate c;
                c.node_orig = inst.node_coords[tour.front()].id;
                c.node = inst.node_coords[i].id;
                c.dist = dist;
                cl.push_back(c);
            }
        }

        for (int i = 1; i < inst.node_coords.size(); i++) {
            int dist = inst.dist(inst.node_coords[tour.back()], inst.node_coords[i]);
            if (i != tour.back() && !visited[i]) {
                Candidate c;
                c.node_orig = inst.node_coords[tour.back()].id;
                c.node = inst.node_coords[i].id;
                c.dist = dist;
                cl.push_back(c);
            }
        }
        Candidate chosen_candidate = choose_candidate(cl, params, randmt);

        if (chosen_candidate.node_orig == inst.node_coords[tour.front()].id) {
            this->tour.push_front(chosen_candidate.node);
            visited[chosen_candidate.node] = true;
        }
        else if (chosen_candidate.node_orig == inst.node_coords[tour.back()].id) {
            this->tour.push_back(chosen_candidate.node);
            visited[chosen_candidate.node] = true;
        }
    }
}