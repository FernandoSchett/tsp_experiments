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
void update_elite_group(std::vector<Tour>& elite_group, Tour& tour, int elite_size);  
bool is_equal(Tour& tour1, Tour& tour2);
#endif