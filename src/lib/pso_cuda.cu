#include "pso_cuda.hpp"

#ifdef USE_CUDA
#include <cuda_runtime.h>
#include <iostream>
#include <vector>
#include <limits>

__global__ void fitness_kernel(const int* d_particles, double* d_fitness, 
                               const int* d_distance_matrix, int n_nodes) {
    int p = blockIdx.x * blockDim.x + threadIdx.x;
    if (p >= n_nodes) return;
    
    double fitness = 0.0;
    for (int i = 0; i < n_nodes - 1; i++) {
        int from = d_particles[p * n_nodes + i];
        int to = d_particles[p * n_nodes + i + 1];
        int d = d_distance_matrix[from * n_nodes + to];
        fitness += d;
    }
    d_fitness[p] = fitness;
}

void pso_gpu(Tour &best_tour, IData &idata, Parameters &params, 
             CPUTime &cpu_time, std::mt19937 &randmt) {
    get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);

    int n_particles = params.n_particles;
    int n_iterations = params.iterations;
    int n_nodes = idata.n_nodes;

    std::vector<int> h_particles(n_particles * n_nodes);
    std::vector<double> h_fitness(n_particles);
    std::vector<int> base_route(n_nodes);
    
    for (int i = 0; i < n_nodes; i++) {
        base_route[i] = i;
    }
    for (int p = 0; p < n_particles; p++) {
        std::vector<int> route = base_route;
        std::shuffle(route.begin(), route.end(), randmt);
        for (int i = 0; i < n_nodes; i++) {
            h_particles[p * n_nodes + i] = route[i];
        }
    }

    int *d_distance_matrix;
    size_t matrix_size = n_nodes * n_nodes * sizeof(int);
    cudaMalloc((void**)&d_distance_matrix, matrix_size);
    cudaMemcpy(d_distance_matrix, idata.distances[0].data(), matrix_size, cudaMemcpyHostToDevice);

    int *d_particles;
    double *d_fitness;
    size_t particles_size = n_particles * n_nodes * sizeof(int);
    size_t fitness_size = n_particles * sizeof(double);
    cudaMalloc((void**)&d_particles, particles_size);
    cudaMalloc((void**)&d_fitness, fitness_size);

    std::vector<int> global_best_position(n_nodes);
    double global_best_fitness = std::numeric_limits<double>::infinity();

    for (int iter = 0; iter < n_iterations; iter++) {
        cudaMemcpy(d_particles, h_particles.data(), particles_size, cudaMemcpyHostToDevice);

        int threadsPerBlock = 256;
        int blocks = (n_particles + threadsPerBlock - 1) / threadsPerBlock;
        fitness_kernel<<<blocks, threadsPerBlock>>>(d_particles, d_fitness, d_distance_matrix, n_nodes);
        cudaDeviceSynchronize();

        cudaMemcpy(h_fitness.data(), d_fitness, fitness_size, cudaMemcpyDeviceToHost);

        int best_index = 0;
        for (int p = 0; p < n_particles; p++) {
            if (h_fitness[p] < global_best_fitness) {
                global_best_fitness = h_fitness[p];
                best_index = p;
            }
        }
        for (int i = 0; i < n_nodes; i++) {
            global_best_position[i] = h_particles[best_index * n_nodes + i];
        }

        for (int p = 0; p < n_particles; p++) {
            std::vector<int> current_route(n_nodes);
            for (int i = 0; i < n_nodes; i++) {
                current_route[i] = h_particles[p * n_nodes + i];
            }
            std::vector<int> new_route = heuristic_crossover(current_route, global_best_position, idata, randmt);
            for (int i = 0; i < n_nodes; i++) {
                h_particles[p * n_nodes + i] = new_route[i];
            }
        }
    }

    best_tour.tour.clear();
    for (int city : global_best_position)
        best_tour.tour.push_back(city);
    best_tour.sol_value = global_best_fitness;

    cudaFree(d_particles);
    cudaFree(d_fitness);
    cudaFree(d_distance_matrix);

    get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
    cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
}
#endif
