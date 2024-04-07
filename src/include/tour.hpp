#ifndef tour_class
#define tour_class

#include "io_inst.hpp"
#include <iostream>
#include <vector>
#include <list>

class Tour {
public:
    std::list<int> tour;
    int sol_value;

    void double_sided_nn_heur(IData& inst, Parameters& params);
    bool is_tour_valid(IData& inst);
    void print_tour();
};

#endif