#ifndef multi_start_heuristics
#define multi_start_heuristics

#include "io_inst.hpp"
#include "parameters.hpp"
#include "get_sys_time.hpp"
#include "tour.hpp"
#include "stop_criterion.hpp"

void multist_semi_nn_heur(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt);
void multist_semi_dsnn_heur(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt);

#endif