#ifndef tour_class
#define tour_class

#include "io_inst.hpp"
#include "get_sys_time.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <filesystem>

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

    void nn_heur(IData& inst, Parameters& params);
    void semi_nn_heur(IData& inst, Parameters& params, std::mt19937& randmt);

    void two_opt_first_imprv(IData& inst, Parameters& params, CPUTime& cpu_time);
    void two_opt_best_imprv(IData& inst, Parameters& params, CPUTime& cpu_time);

    void two_opt_best_imprv_cand_list(IData& inst, Parameters& params, CPUTime& cpu_time);
    void two_opt_first_imprv_circ_search(IData& inst, Parameters& params, CPUTime& cpu_time);

    void calc_tour_cost(IData& inst);
    bool is_tour_valid(IData& inst);
    void print_tour();
    void save_time_result(IData& idata, Parameters& params, CPUTime& cpu_time);
    void save_solution_to_file(IData& idata, Parameters& params);
    void read_solution_file(IData& idata, Parameters& params);
};

#endif