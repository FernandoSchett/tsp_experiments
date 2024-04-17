#include "tour.hpp"


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