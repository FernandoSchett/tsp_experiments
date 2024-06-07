#include "multi_start.hpp"

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