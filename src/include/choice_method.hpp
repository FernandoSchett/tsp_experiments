#ifndef choice_method_functions
#define choice_method_functions

#include "tour.hpp"
#include "parameters.hpp"
#include "io_inst.hpp"
#include "get_sys_time.hpp"
#include "multi_start.hpp"
#include "local_search.hpp"
#include "grasp.hpp"
#include "path_relinking.hpp"
#include "stop_criterion.hpp"

void run_choice_method(Tour& best_tour, IData& idata, Parameters& param, CPUTime& cpu_time, std::mt19937& randmt);

#endif