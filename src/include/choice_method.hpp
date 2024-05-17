#ifndef choice_method_functions
#define choice_method_functions

#include "tour.hpp"
#include "parameters.hpp"
#include "io_inst.hpp"
#include "get_sys_time.hpp"

bool is_stop_criterion_satsfied(Parameters& params, double cpu_time, int i);
void multist_semi_nn_heur(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt);
void multist_semi_dsnn_heur(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt);
void run_choice_method(Tour& best_tour, IData& idata, Parameters& param, CPUTime& cpu_time, std::mt19937& randmt);
void local_search(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time);
void grasp(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt);

#endif