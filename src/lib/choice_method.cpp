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
		if(idata.n_nodes <= 100){
			params.maxtime = params.maxtime/4; 
		}else if(idata.n_nodes < 2500){
			params.maxtime = params.maxtime/2;
		}
		grasp(best_tour, idata, params, cpu_time, randmt);
	}
	else {
		printf("ERROR: No choice method selected.\n");
		exit(0);
	}

}

bool is_stop_criterion_satsfied(Parameters& params, int sol_value, double t, int i) {
	if (params.stop_criterion == "iter") {
		return i >= params.iterations;
	}
	else if (params.stop_criterion == "look4") {
		return t >= params.maxtime || sol_value <= params.look4;
	}
	else if (params.stop_criterion == "time") {
		return t >= params.maxtime;
	}
	else {
		printf("ERROR: stop criterion selected is not available\n");
		exit(0);
	}
}

void multist_semi_nn_heur(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	best_tour.nn_heur(idata, params);
	printf("%d\n", best_tour.sol_value);

	int i = 0;
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
	while (!is_stop_criterion_satsfied(params, 0, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i)) {
		Tour tour;
		tour.semi_nn_heur(idata, params, randmt);

		if (tour.sol_value < best_tour.sol_value) {
			best_tour = tour;
		}

		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_CPU_inicial);
		printf("%d %d %lf %d\n", best_tour.sol_value, tour.sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i);
		i++;
	}
	get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
	cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
}

void multist_semi_dsnn_heur(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	best_tour.double_sided_nn_heur(idata, params);
	printf("%d\n", best_tour.sol_value);

	int i = 0;
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
	while (!is_stop_criterion_satsfied(params, 0, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i)) {
		Tour tour;
		tour.semi_double_sided_nn_heur(idata, params, randmt);

		if (tour.sol_value < best_tour.sol_value) {
			best_tour = tour;
		}

		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_CPU_inicial);
		printf("%d %d %lf %d\n", best_tour.sol_value, tour.sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i);
		i++;
	}
	get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
	cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
}

void local_search(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time) {

	if (params.local_search == "two_opt_best_imprv") {
		best_tour.two_opt_best_imprv(idata, params, cpu_time);
	}
	else if (params.local_search == "two_opt_first_imprv") {
		best_tour.two_opt_first_imprv(idata, params, cpu_time);
	}
	else if (params.local_search == "two_opt_best_imprv_cand_list") {
		best_tour.two_opt_best_imprv_cand_list(idata, params, cpu_time);
	}
	else if (params.local_search == "two_opt_first_imprv_circ_search") {
		best_tour.two_opt_first_imprv_circ_search(idata, params, cpu_time);
	}
	else {
		printf("ERROR: Local search provided does not exist.");
		exit(0);
	}

	return;
}

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