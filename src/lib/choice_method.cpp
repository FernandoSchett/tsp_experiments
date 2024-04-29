#include "choice_method.hpp"

void run_choice_method(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	cpu_time.total_s_CPU = 0;

	if (params.choice_method == "nn_heur") {
		if (params.stop_criterion == "iter") {
			for (int i = 0; i < params.iterations; i++) {
				best_tour.tour.clear();
				get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
				best_tour.nn_heur(idata, params);
				get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
				cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
			}
		}
		else if (params.stop_criterion == "time") {
			while (cpu_time.total_s_CPU < params.maxtime) {
				best_tour.tour.clear();
				get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
				best_tour.nn_heur(idata, params);
				get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
				cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
			}
		}
	}
	else if (params.choice_method == "dsnn_heur") {
		if (params.stop_criterion == "iter") {
			for (int i = 0; i < params.iterations; i++) {
				best_tour.tour.clear();
				get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
				best_tour.double_sided_nn_heur(idata, params);
				get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
				cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
			}
		}
		else if (params.stop_criterion == "time") {
			while (cpu_time.total_s_CPU < params.maxtime) {
				best_tour.tour.clear();
				get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
				best_tour.double_sided_nn_heur(idata, params);
				get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
				cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
			}
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
	else {
		printf("ERROR: No choice method selected.\n");
		exit(0);
	}

	best_tour.calc_tour_cost(idata);
}

bool is_stop_criterion_satsfied(Parameters& params, CPUTime& cpu_time, int i) {
	if (params.stop_criterion == "iter") {
		return i >= params.iterations;
	}
	else if (params.stop_criterion == "time") {
		return cpu_time.s_CPU_during - cpu_time.s_CPU_inicial >= params.maxtime;
	}
	else {
		printf("ERROR: stop criterion selected is not available\n");
		exit(0);
	}
}

void multist_semi_nn_heur(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	best_tour.nn_heur(idata, params);
	best_tour.calc_tour_cost(idata);
	printf("%d\n", best_tour.sol_value);

	int i = 0;
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
	while (!is_stop_criterion_satsfied(params, cpu_time, i)) {
		Tour tour;
		tour.semi_nn_heur(idata, params, randmt);
		tour.calc_tour_cost(idata);

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
	best_tour.calc_tour_cost(idata);
	printf("%d\n", best_tour.sol_value);

	int i = 0;
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
	while (!is_stop_criterion_satsfied(params, cpu_time, i)) {
		Tour tour;
		tour.semi_double_sided_nn_heur(idata, params, randmt);
		tour.calc_tour_cost(idata);

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