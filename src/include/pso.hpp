#ifndef PSO_HPP
#define PSO_HPP

#include "parameters.hpp"
#include "io_inst.hpp"
#include "tour.hpp"
#include "get_sys_time.hpp" 
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <mpi.h>

void pso_multithread(Tour &best_tour, IData &idata, Parameters &params, 
    CPUTime &cpu_time, std::mt19937 &randmt); // Multi-threaded PSO using OpenMP


void pso_multiprocess(Tour &best_tour, IData &idata, Parameters &params, 
    CPUTime &cpu_time, std::mt19937 &randmt); // Multi-process PSO using MPI

void pso_hibrid(Tour &best_tour, IData &idata, Parameters &params, 
                CPUTime &cpu_time, std::mt19937 &randmt); // Hybrid PSO (MPI + OpenMP)

// Structure representing a particle (candidate route)
struct Particle {
    std::vector<int> position;       // Current route (vector of node indices)
    std::vector<int> best_position;  // Best route found by this particle
    double best_fitness;             // Fitness value (cost) of the best route
};

// Auxiliary functions

double compute_fitness(const std::vector<int>& route, const IData &idata); // Calculates the total cost (fitness) of a route
int get_distance(int city1, int city2, const IData &idata); // Returns the distance between two cities
std::vector<int> heuristic_crossover(std::vector<int> parent1, std::vector<int> parent2, 
                                     const IData &idata, std::mt19937 &randmt); // Performs a heuristic crossover between two routes

// PSO Implementations
void pso(Tour &best_tour, IData &idata, Parameters &params, 
         CPUTime &cpu_time, std::mt19937 &randmt); // Serial PSO implementation

#endif // PSO_HPP
