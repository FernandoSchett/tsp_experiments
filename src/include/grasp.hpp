#ifndef grasp_heuristics
#define grasp_heuristics

#include "io_inst.hpp"
#include "parameters.hpp"
#include "get_sys_time.hpp"
#include "tour.hpp"
#include "stop_criterion.hpp"
#include "local_search.hpp"
#include "path_relinking.hpp"

void grasp(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt);
void grasp_pr(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt);

#endif