#ifndef tour_class
#define tour_class

#include "io_inst.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

class Tour {
public:
    std::list<int> tour;
    int sol_value;

    void double_sided_nn_heur(IData& inst, Parameters& params);
    void saving_heur(IData& inst, Parameters& params);
    void nn_heur(IData& inst, Parameters& params);
    bool is_tour_valid(IData& inst);
    void print_tour();
};

#endif