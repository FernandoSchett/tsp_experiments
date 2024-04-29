#ifndef choice_method_functions
#define choice_method_functions

#include "tour.hpp"
#include "parameters.hpp"
#include "io_inst.hpp"
#include "get_sys_time.hpp"

void run_choice_method(Tour &best_tour, IData &idata, Parameters &param, CPUTime &cpu_time, std::mt19937& randmt);

#endif