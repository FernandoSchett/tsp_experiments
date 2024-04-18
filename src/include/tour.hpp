#ifndef tour_class
#define tour_class

#include "io_inst.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <limits.h>
#include <algorithm>

struct Candidate {
    int node_orig;
    int node;
    int dist;
};

class Tour {
public:
    std::list<int> tour;
    int sol_value;

    void double_sided_nn_heur(IData& inst, Parameters& params);
    void semi_double_sided_nn_heur(IData& inst, Parameters& params, std::mt19937& randmt);
    void calc_tour_cost(IData& inst);
    void nn_heur(IData& inst, Parameters& params);
    bool is_tour_valid(IData& inst);
    void print_tour();
};

#endif