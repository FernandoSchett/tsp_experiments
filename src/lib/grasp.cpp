#include "grasp.hpp"


void grasp(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);

	printf("bestsol;currsol;grasp_sol_value;currtime;iteration\n");
	
	best_tour.semi_nn_heur(idata, params, randmt);
	int greedy_sol_value = best_tour.sol_value;
	local_search(best_tour, idata, params, cpu_time);
	printf("%d;%d;%d;%lf;%d\n", best_tour.sol_value, best_tour.sol_value, greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, 1);

	int i = 2;
	
	while (!is_stop_criterion_satsfied(params, best_tour.sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i)) {
		Tour tour;
		tour.semi_nn_heur(idata, params, randmt);
		int semi_greedy_sol_value = tour.sol_value;
		local_search(tour, idata, params, cpu_time);

		if (tour.sol_value < best_tour.sol_value) {
			best_tour = tour;
		}

		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_CPU_inicial);
		printf("%d;%d;%d;%lf;%d\n", best_tour.sol_value, tour.sol_value, semi_greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i);
		i++;
	}
	get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
	cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
}

void grasp_pr(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);

	printf("bestsol;currsol;grasp_sol_value;currtime;iteration\n");
	
	best_tour.nn_heur(idata, params);
	int greedy_sol_value = best_tour.sol_value;
	local_search(best_tour, idata, params, cpu_time);
	printf("%d;%d;%d;%lf;%d\n", best_tour.sol_value, best_tour.sol_value, greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, 1);

	int i = 2;
	
	while (!is_stop_criterion_satsfied(params, best_tour.sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i)) {
		Tour tour;
		tour.semi_nn_heur(idata, params, randmt);
		int semi_greedy_sol_value = tour.sol_value;
		local_search(tour, idata, params, cpu_time);
		
		if(params.pr_mode == "f"){
			path_relinking(best_tour, tour, idata);
		}else if(params.pr_mode == "b"){
			path_relinking(tour, best_tour, idata);
		}else if(params.pr_mode == "bf"){
			path_relinking(best_tour, tour, idata);
			path_relinking(tour, best_tour, idata);
		}else if(params.pr_mode == "m"){
			path_relinking_mixed(tour, best_tour, idata);
		}else{
			printf("ERROR: No PR mode avaliabe.\n");
			exit(0);
		}

		if (tour.sol_value < best_tour.sol_value) {
			best_tour = tour;
		}
		
		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_CPU_inicial);
		printf("%d;%d;%d;%lf;%d\n", best_tour.sol_value, tour.sol_value, semi_greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i);
		i++;
	}
	get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
	cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
}
