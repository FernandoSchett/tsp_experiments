#ifndef path_relinking_functions
#define path_relinking_functions

#include "tour.hpp"
#include "parameters.hpp"
#include "io_inst.hpp"
#include "local_search.hpp"

Tour path_relinking(Tour& guide_tour, Tour& inicial_tour, IData& idata, Parameters& params, CPUTime& dummy_time);
Tour path_relinking_mixed(Tour& guide_tour, Tour& inicial_tour, IData& idata, Parameters& params, CPUTime& dummy_time);
Tour get_best_neighbor(Tour& guide_tour, Tour& inicial_tour, IData& inst);
int neighborhood_size(Tour& inter_sol, Tour& guide_tour);
#endif