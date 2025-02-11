/**
 * -----------------------------------------------------------------------------  
 * File Name:          pso.cpp  
 * Authors:            Seu Nome  
 * Last Modified Date: dd/mm/2025  
 * Purpose:            Implementação do PSO para o TSP, incluindo versões  
 *                     paralelas (multithread com OpenMP, multiprocess com MPI,  
 *                     híbrida e GPU com CUDA).
 * 
 * Notas:
 * - O PSO (Particle Swarm Optimization) é aplicado sobre uma população de  
 *   partículas (rotas candidatas), onde cada partícula é atualizada utilizando  
 *   um crossover heurístico entre seu “personal best” e o “global best”.
 * - Em cada execução a função inicia e finaliza a contagem do tempo (usando  
 *   get_cpu_time) de forma semelhante às outras heurísticas.
 * - O número de partículas, threads e processos são configuráveis via parâmetros.
 * -----------------------------------------------------------------------------  
 */

 #include "pso.hpp"
 #include "parameters.hpp"
 #include "io_inst.hpp"
 #include "tour.hpp"
 #include "get_sys_time.hpp"
 
 #include <vector>
 #include <algorithm>
 #include <random>
 #include <limits>
 #include <iostream>
 
 #ifdef _OPENMP
 #include <omp.h>
 #endif
 
 #ifdef USE_MPI
 #include <mpi.h>
 #endif
 
 // ********************************************************************
 // Função: compute_fitness  
 // Calcula o custo total (fitness) de uma rota (soma das distâncias entre nós)
 // ********************************************************************
 double compute_fitness(const std::vector<int>& route, const IData &idata) {
     double total_distance = 0.0;
     for (size_t i = 0; i < route.size() - 1; i++) {
         int from = route[i];
         int to = route[i+1];
         int d = idata.distances[from][to];
         if (d <= 0) {
             return std::numeric_limits<double>::infinity();
         }
         total_distance += d;
     }
     return total_distance;
 }
 
 // ********************************************************************
 // Função: get_distance  
 // Retorna a distância entre duas cidades (nós). Caso não exista, retorna INT_MAX.
 // ********************************************************************
 int get_distance(int city1, int city2, const IData &idata) {
     int d = idata.distances[city1][city2];
     return (d > 0 ? d : INT_MAX);
 }
 
 // ********************************************************************
 // Função: heuristic_crossover  
 // Recebe duas rotas (pais) e gera uma nova rota (filho) combinando ambas de forma  
 // heurística – semelhante ao código Python fornecido.
 // ********************************************************************
 std::vector<int> heuristic_crossover(std::vector<int> parent1, std::vector<int> parent2, 
                                        const IData &idata, std::mt19937 &randmt) {
     int n = static_cast<int>(parent1.size());
     std::uniform_int_distribution<int> dist(0, n - 1);
     int idx = dist(randmt);
     int v = parent1[idx];
 
     // Remove v (se necessário) e o insere na posição inicial em ambas as rotas
     auto it = std::find(parent1.begin(), parent1.end(), v);
     if(it != parent1.end()){
         parent1.erase(it);
     }
     parent1.insert(parent1.begin(), v);
 
     it = std::find(parent2.begin(), parent2.end(), v);
     if(it != parent2.end()){
         parent2.erase(it);
     }
     parent2.insert(parent2.begin(), v);
 
     std::vector<int> child;
     child.push_back(v);
 
     int i = 1, j = 1;
     while(i < n && j < n) {
         bool in_child_p1 = (std::find(child.begin(), child.end(), parent1[i]) != child.end());
         bool in_child_p2 = (std::find(child.begin(), child.end(), parent2[j]) != child.end());
         if(in_child_p1 && in_child_p2) {
             i++; j++;
         } else if(in_child_p1) {
             child.push_back(parent2[j]);
             j++;
         } else if(in_child_p2) {
             child.push_back(parent1[i]);
             i++;
         } else {
             int last_city = child.back();
             int d1 = get_distance(last_city, parent1[i], idata);
             int d2 = get_distance(last_city, parent2[j], idata);
             if(d1 < d2) {
                 child.push_back(parent1[i]);
                 i++;
             } else {
                 child.push_back(parent2[j]);
                 j++;
             }
         }
     }
     while(child.size() < static_cast<size_t>(n)) {
         if(i < n && std::find(child.begin(), child.end(), parent1[i]) == child.end()){
             child.push_back(parent1[i]);
         }
         i++;
         if(child.size() < static_cast<size_t>(n) && j < n && 
            std::find(child.begin(), child.end(), parent2[j]) == child.end()){
             child.push_back(parent2[j]);
         }
         j++;
     }
     return child;
 }
 
 // ********************************************************************
 // Função: pso (versão serial)
 // ********************************************************************
 void pso(Tour &best_tour, IData &idata, Parameters &params, 
          CPUTime &cpu_time, std::mt19937 &randmt) {
     get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
 
     int n_particles = params.n_particles;
     int n_iterations = params.iterations;
     std::vector<Particle> particles(n_particles);
 
     std::vector<int> base_route(idata.n_nodes);
     for (int i = 0; i < idata.n_nodes; i++) {
         base_route[i] = i;
     }
 
     for (int p = 0; p < n_particles; p++) {
         particles[p].position = base_route;
         std::shuffle(particles[p].position.begin(), particles[p].position.end(), randmt);
         particles[p].best_position = particles[p].position;
         particles[p].best_fitness = compute_fitness(particles[p].position, idata);
     }
 
     std::vector<int> global_best_position = particles[0].position;
     double global_best_fitness = particles[0].best_fitness;
 
     for (int iter = 0; iter < n_iterations; iter++) {
         for (int p = 0; p < n_particles; p++) {
             double current_fitness = compute_fitness(particles[p].position, idata);
             if (current_fitness < particles[p].best_fitness) {
                 particles[p].best_fitness = current_fitness;
                 particles[p].best_position = particles[p].position;
             }
             if (current_fitness < global_best_fitness) {
                 global_best_fitness = current_fitness;
                 global_best_position = particles[p].position;
             }
         }
         for (int p = 0; p < n_particles; p++) {
             particles[p].position = heuristic_crossover(particles[p].best_position, 
                                                           global_best_position, idata, randmt);
         }
     }
 
     best_tour.tour.clear();
     for (int city : global_best_position) {
         best_tour.tour.push_back(city);
     }
     best_tour.sol_value = global_best_fitness;
 
     get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
     cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
 }
 
 // ********************************************************************
 // Função: pso_multithread (usando OpenMP)
 // ********************************************************************
 void pso_multithread(Tour &best_tour, IData &idata, Parameters &params, 
                      CPUTime &cpu_time, std::mt19937 &randmt) {
     get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
 
     omp_set_num_threads(params.n_threads);
 
     int n_particles = params.n_particles;
     int n_iterations = params.iterations;
     std::vector<Particle> particles(n_particles);
     std::vector<int> base_route(idata.n_nodes);
     for (int i = 0; i < idata.n_nodes; i++) {
         base_route[i] = i;
     }
 
     // Inicialização paralela das partículas
     #pragma omp parallel for
     for (int p = 0; p < n_particles; p++) {
         std::mt19937 thread_rand(randmt());
         particles[p].position = base_route;
         std::shuffle(particles[p].position.begin(), particles[p].position.end(), thread_rand);
         particles[p].best_position = particles[p].position;
         particles[p].best_fitness = compute_fitness(particles[p].position, idata);
     }
 
     std::vector<int> global_best_position = particles[0].position;
     double global_best_fitness = particles[0].best_fitness;
 
     for (int iter = 0; iter < n_iterations; iter++) {
         #pragma omp parallel for
         for (int p = 0; p < n_particles; p++) {
             double current_fitness = compute_fitness(particles[p].position, idata);
             if (current_fitness < particles[p].best_fitness) {
                 particles[p].best_fitness = current_fitness;
                 particles[p].best_position = particles[p].position;
             }
             #pragma omp critical
             {
                 if (current_fitness < global_best_fitness) {
                     global_best_fitness = current_fitness;
                     global_best_position = particles[p].position;
                 }
             }
         }
         #pragma omp parallel for
         for (int p = 0; p < n_particles; p++) {
             std::mt19937 thread_rand(randmt());
             particles[p].position = heuristic_crossover(particles[p].best_position, 
                                                           global_best_position, idata, thread_rand);
         }
     }
 
     best_tour.tour.clear();
     for (int city : global_best_position)
         best_tour.tour.push_back(city);
     best_tour.sol_value = global_best_fitness;
 
     get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
     cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
 }
 
 // ********************************************************************
 // Função: pso_multiprocess (usando MPI)
 // Cada processo trabalha com um conjunto local de partículas e, a cada iteração,  
 // os melhores locais são compartilhados para atualizar o global best.
 // ********************************************************************
 void pso_multiprocess(Tour &best_tour, IData &idata, Parameters &params, 
                       CPUTime &cpu_time, std::mt19937 &randmt) {
     get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
 
     int rank, size;
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &size);
 
     // Verifica se o número de processos corresponde ao parâmetro (opcional)
     if (rank == 0 && size != params.n_processes) {
         std::cerr << "Aviso: O número de processos MPI (" << size 
                   << ") difere do parâmetro n_processes (" << params.n_processes << ")." << std::endl;
     }
 
     int n_particles = params.n_particles; // Número de partículas por processo
     int n_iterations = params.iterations;
     std::vector<Particle> particles(n_particles);
     std::vector<int> base_route(idata.n_nodes);
     for (int i = 0; i < idata.n_nodes; i++)
         base_route[i] = i;
     for (int p = 0; p < n_particles; p++) {
         particles[p].position = base_route;
         std::shuffle(particles[p].position.begin(), particles[p].position.end(), randmt);
         particles[p].best_position = particles[p].position;
         particles[p].best_fitness = compute_fitness(particles[p].position, idata);
     }
 
     std::vector<int> global_best_position = particles[0].position;
     double global_best_fitness = particles[0].best_fitness;
 
     for (int iter = 0; iter < n_iterations; iter++) {
         double local_best_fitness = std::numeric_limits<double>::infinity();
         std::vector<int> local_best_position(idata.n_nodes);
         for (int p = 0; p < n_particles; p++) {
             double current_fitness = compute_fitness(particles[p].position, idata);
             if (current_fitness < particles[p].best_fitness) {
                 particles[p].best_fitness = current_fitness;
                 particles[p].best_position = particles[p].position;
             }
             if (current_fitness < local_best_fitness) {
                 local_best_fitness = current_fitness;
                 local_best_position = particles[p].position;
             }
         }
 
         std::vector<double> gathered_fitness(size);
         std::vector<int> gathered_routes(size * idata.n_nodes);
         MPI_Allgather(&local_best_fitness, 1, MPI_DOUBLE, gathered_fitness.data(), 1, MPI_DOUBLE, MPI_COMM_WORLD);
         MPI_Allgather(local_best_position.data(), idata.n_nodes, MPI_INT, gathered_routes.data(),
                       idata.n_nodes, MPI_INT, MPI_COMM_WORLD);
 
         global_best_fitness = local_best_fitness;
         global_best_position = local_best_position;
         for (int i = 0; i < size; i++) {
             if (gathered_fitness[i] < global_best_fitness) {
                 global_best_fitness = gathered_fitness[i];
                 global_best_position.assign(gathered_routes.begin() + i * idata.n_nodes,
                                             gathered_routes.begin() + (i+1) * idata.n_nodes);
             }
         }
 
         for (int p = 0; p < n_particles; p++) {
             particles[p].position = heuristic_crossover(particles[p].best_position, 
                                                           global_best_position, idata, randmt);
         }
     }
 
     best_tour.tour.clear();
     for (int city : global_best_position)
         best_tour.tour.push_back(city);
     best_tour.sol_value = global_best_fitness;
 
     get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
     cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);

 }
 
 // ********************************************************************
 // Função: pso_hibrid (MPI + OpenMP)
 // Combina a atualização local paralelizada (OpenMP) com a comunicação global via MPI.
 // ********************************************************************
 void pso_hibrid(Tour &best_tour, IData &idata, Parameters &params, 
                 CPUTime &cpu_time, std::mt19937 &randmt) {
     get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
 
     int rank, size;
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &size);
 
     int n_particles = params.n_particles;
     int n_iterations = params.iterations;
     std::vector<Particle> particles(n_particles);
     std::vector<int> base_route(idata.n_nodes);
     for (int i = 0; i < idata.n_nodes; i++)
         base_route[i] = i;
     
 
     #pragma omp parallel for
     for (int p = 0; p < n_particles; p++) {
         std::mt19937 thread_rand(randmt());
         particles[p].position = base_route;
         std::shuffle(particles[p].position.begin(), particles[p].position.end(), thread_rand);
         particles[p].best_position = particles[p].position;
         particles[p].best_fitness = compute_fitness(particles[p].position, idata);
     }
 
     std::vector<int> global_best_position = particles[0].position;
     double global_best_fitness = particles[0].best_fitness;
 
     for (int iter = 0; iter < n_iterations; iter++) {
         double local_best_fitness = std::numeric_limits<double>::infinity();
         std::vector<int> local_best_position(idata.n_nodes);
         
         #pragma omp parallel for
         for (int p = 0; p < n_particles; p++) {
             double current_fitness = compute_fitness(particles[p].position, idata);
             if (current_fitness < particles[p].best_fitness) {
                 particles[p].best_fitness = current_fitness;
                 particles[p].best_position = particles[p].position;
             }
             #pragma omp critical
             {
                 if (current_fitness < local_best_fitness) {
                     local_best_fitness = current_fitness;
                     local_best_position = particles[p].position;
                 }
             }
         }
 
         std::vector<double> gathered_fitness(size);
         std::vector<int> gathered_routes(size * idata.n_nodes);
         MPI_Allgather(&local_best_fitness, 1, MPI_DOUBLE, gathered_fitness.data(), 1, MPI_DOUBLE, MPI_COMM_WORLD);
         MPI_Allgather(local_best_position.data(), idata.n_nodes, MPI_INT, gathered_routes.data(),
                       idata.n_nodes, MPI_INT, MPI_COMM_WORLD);
 
         global_best_fitness = local_best_fitness;
         global_best_position = local_best_position;
         for (int i = 0; i < size; i++) {
             if (gathered_fitness[i] < global_best_fitness) {
                 global_best_fitness = gathered_fitness[i];
                 global_best_position.assign(gathered_routes.begin() + i * idata.n_nodes,
                                             gathered_routes.begin() + (i+1) * idata.n_nodes);
             }
         }
 
         #pragma omp parallel for
         for (int p = 0; p < n_particles; p++) {
             std::mt19937 thread_rand(randmt());
             particles[p].position = heuristic_crossover(particles[p].best_position, 
                                                           global_best_position, idata, thread_rand);
         }
     }
 
     best_tour.tour.clear();
     for (int city : global_best_position)
         best_tour.tour.push_back(city);
     best_tour.sol_value = global_best_fitness;
 
     get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
     cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);

 }
 