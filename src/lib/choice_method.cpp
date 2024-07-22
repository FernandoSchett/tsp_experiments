/*
 * -----------------------------------------------------------------------------
 * File Name:          choice_method.cpp
 * Authors:            Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
 * Last Modified Date: 22/07/2024
 * Purpose: 		  Functions responsible for choosing the running the choice method.            
 * Notes:
 * - Nearest Neighbor and Semi-Randomized Nearest Neighbor [3]
 * - Double-Sided Nearest Neighbor and Semi-Randomized Double-Sided Nearest Neighbor [3]
 * - Multi-Start Semi-Randomized Nearest Neighbor and Multi-Start Semi-Randomized Double-Sided Nearest Neighbor [3]
 * - Local Search [3]
 * - GRASP [3]
 * - Grasp + Path Relinking [3]
 * - Grasp + Path Relinking + Restart Techniques [3]
 * -----------------------------------------------------------------------------
 */

#include "choice_method.hpp"

void run_choice_method(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	cpu_time.total_s_CPU = 0;

	if (params.choice_method == "nn_heur") {
		int i = 0;
		while (!is_stop_criterion_satsfied(params, 0, cpu_time.total_s_CPU, i)) {
			best_tour.tour.clear();
			get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
			best_tour.nn_heur(idata, params);
			get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
			cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
			i++;
		}
	}
	else if (params.choice_method == "dsnn_heur") {
		int i = 0;
		while (!is_stop_criterion_satsfied(params, 0, cpu_time.total_s_CPU, i)) {
			best_tour.tour.clear();
			get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
			best_tour.double_sided_nn_heur(idata, params);
			get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
			cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
			i++;
		}
	}
	else if (params.choice_method == "semi_nn_heur") {
		get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
		best_tour.semi_nn_heur(idata, params, randmt);
		get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
		cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
	}
	else if (params.choice_method == "semi_dsnn_heur") {
		get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
		best_tour.semi_double_sided_nn_heur(idata, params, randmt);
		get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
		cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
	}
	else if (params.choice_method == "multist_semi_nn_heur") {
		multist_semi_nn_heur(best_tour, idata, params, cpu_time, randmt);
	}
	else if (params.choice_method == "multist_semi_dsnn_heur") {
		multist_semi_dsnn_heur(best_tour, idata, params, cpu_time, randmt);
	}
	else if (params.choice_method == "local_search") {
		best_tour.read_solution_file(idata, params);
		local_search(best_tour, idata, params, cpu_time);
	}
	else if (params.choice_method == "grasp"){
		//if(idata.n_nodes <= 100){
		//	params.maxtime = params.maxtime/4; 
		//}else if(idata.n_nodes < 2500){
		//	params.maxtime = params.maxtime/2;
		//}
		grasp(best_tour, idata, params, cpu_time, randmt);
	}
	else if(params.choice_method == "grasp_pr"){	
		grasp_pr(best_tour, idata, params, cpu_time, randmt);
	}else if(params.choice_method == "grasp_prr"){
		std::cout << "grasp_prr" << std::endl;	
		grasp_prr(best_tour, idata, params, cpu_time, randmt);
	}else{
		printf("ERROR: No choice method selected.\n");
		exit(0);
	}
}