#include "tour.hpp"
#include "semi_greedy_schemes.hpp"

Candidate cardinality_scheme(std::vector<Candidate>& rcl, Parameters& params, std::mt19937& randmt) {
    int k = std::min(params.k_best, int(rcl.size()));
    int idx_candidate = randmt() % k;
    Candidate chosen_candidate = rcl[idx_candidate];
    return chosen_candidate;
}

Candidate quality_scheme(std::vector<Candidate>& rcl, Parameters& params, std::mt19937& randmt) {
    int c_min = rcl.front().dist;
    int c_max = rcl.back().dist;
    std::vector<Candidate>::iterator ub = upper_bound(
        rcl.begin(),
        rcl.end(),
        c_min + params.alpha * (c_max - c_min),
        [](int val, const Candidate& c) {
            return c.dist > val;
        }
    );
    int k = ub - rcl.begin();
    int idx_candidate = randmt() % k;
    Candidate chosen_candidate = rcl[idx_candidate];
    return chosen_candidate;
}

Candidate choose_candidate(std::vector<Candidate>& rcl, Parameters& params, std::mt19937& randmt) {
    Candidate chosen_candidate;
    if (params.scheme == "k_best") {
        chosen_candidate = cardinality_scheme(rcl, params, randmt);
    }
    else if (params.scheme == "alpha") {
        chosen_candidate = quality_scheme(rcl, params, randmt);
    }
    else {
        exit(0);
    }
    return chosen_candidate;
}

bool rcl_dist_lte_cmp(const Candidate& c1, const Candidate& c2) {
    return c1.dist < c2.dist;
}
