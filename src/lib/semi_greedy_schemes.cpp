#include "tour.hpp"
#include "semi_greedy_schemes.hpp"

Candidate cardinality_scheme(std::vector<Candidate>& cl, Parameters& params, std::mt19937& randmt) {
    int k = std::min(params.k_best, int(cl.size()));
    int idx_candidate = randmt() % k;
    std::partial_sort(cl.begin(), cl.begin() + k, cl.end(), rcl_dist_lte_cmp); // O(n log k)
    Candidate chosen_candidate = cl[idx_candidate];
    return chosen_candidate;
}

Candidate quality_scheme(std::vector<Candidate>& cl, Parameters& params, std::mt19937& randmt) {
    // O(n)
    int c_min = INT_MAX;
    int c_max = 0;
    for (int i = 0; i < cl.size(); i++) {
        c_min = std::min(c_min, cl[i].dist);
        c_max = std::max(c_max, cl[i].dist);
    }
    int max_dist_allowed = c_min + params.alpha * (c_max - c_min);
    std::vector<Candidate> rcl;
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].dist <= max_dist_allowed) {
            rcl.push_back(cl[i]);
        }
    }

    int k = rcl.size();
    int idx_candidate = randmt() % k;
    Candidate chosen_candidate = rcl[idx_candidate];
    return chosen_candidate;
}

Candidate choose_candidate(std::vector<Candidate>& cl, Parameters& params, std::mt19937& randmt) {
    Candidate chosen_candidate;
    if (params.scheme == "k_best") {
        chosen_candidate = cardinality_scheme(cl, params, randmt);
    }
    else if (params.scheme == "alpha") {
        chosen_candidate = quality_scheme(cl, params, randmt);
    }
    else {
        printf("Scheme provided is not available.\n");
        exit(0);
    }
    return chosen_candidate;
}

bool rcl_dist_lte_cmp(const Candidate& c1, const Candidate& c2) {
    return c1.dist < c2.dist;
}
