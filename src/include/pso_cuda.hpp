#ifndef CUDA_PSO_HPP
#define CUDA_PSO_HPP


#include "tour.hpp"
#include "parameters.hpp"
#include "io_inst.hpp"
#include "get_sys_time.hpp"
#include "pso.hpp"
#include <random>
#include <vector>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>


// ********************************************************************
// Kernel CUDA: fitness_kernel
// ********************************************************************
__global__ void fitness_kernel(const int* d_particles, double* d_fitness, 
                               const int* d_distance_matrix, int n_nodes);


void pso_gpu(Tour &best_tour, IData &idata, Parameters &params, 
             CPUTime &cpu_time, std::mt19937 &randmt);


int get_distance(int city1, int city2, const IData &idata); // Returns the distance between two cities

#endif 
