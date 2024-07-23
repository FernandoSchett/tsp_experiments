#ifndef local_search_selector
#define local_search_selector

#include "io_inst.hpp"
#include "parameters.hpp"
#include "get_sys_time.hpp"
#include "tour.hpp"

void local_search(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time);

#endif