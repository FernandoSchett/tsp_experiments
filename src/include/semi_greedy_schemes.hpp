#ifndef semi_greedy_schemes_functions
#define semi_greedy_schemes_functions

Candidate cardinality_scheme(std::vector<Candidate>& rcl, Parameters& params, std::mt19937& randmt);
Candidate quality_scheme(std::vector<Candidate>& rcl, Parameters& params, std::mt19937& randmt);
Candidate choose_candidate(std::vector<Candidate>& rcl, Parameters& params, std::mt19937& randmt);
bool rcl_dist_lte_cmp(const Candidate& c1, const Candidate& c2);

#endif