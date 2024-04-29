#include "choice_method.hpp"

void run_choice_method(Tour &best_tour, IData &idata, Parameters &param, CPUTime &cpu_time, std::mt19937& randmt){
	cpu_time.total_s_CPU = 0;

	if (param.choice_method == "nn_heur") {
		for (int i = 0; i < param.iterations; i++) {
			best_tour.tour.clear();
			get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
			best_tour.nn_heur(idata, param);
			get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
			cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
		}
	}
	else if (param.choice_method == "dsnn_heur") {
		for (int i = 0; i < param.iterations; i++) {
			best_tour.tour.clear();
			get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
			best_tour.double_sided_nn_heur(idata, param);
			get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
			cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
		}
	}
	else if (param.choice_method == "semi_nn_heur") {
		get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
		best_tour.semi_nn_heur(idata, param, randmt);
		get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
		cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
	}
	else if (param.choice_method == "semi_dsnn_heur") {
		get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
		best_tour.semi_double_sided_nn_heur(idata, param, randmt);
		get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
		cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
	}
	else if (param.choice_method == "multist_semi_nn_heur") {
		int contador = 0;
		best_tour.nn_heur(idata, param);
		best_tour.calc_tour_cost(idata);
		printf("%d %d\n", best_tour.sol_value, contador);

		get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
		while (contador < param.iterations) {
			Tour tour;
			tour.semi_nn_heur(idata, param, randmt);
			tour.calc_tour_cost(idata);

			if (tour.sol_value < best_tour.sol_value) {
				best_tour = tour;
			}

			get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_CPU_inicial);
			printf("%d %d %lf %d\n", best_tour.sol_value, tour.sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, contador);
			contador++;
		}
		get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
		cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
	}
	else if (param.choice_method == "multist_semi_dsnn_heur") {
		best_tour.double_sided_nn_heur(idata, param);
		best_tour.calc_tour_cost(idata);

		get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
		while (cpu_time.s_CPU_during - cpu_time.s_CPU_inicial < param.maxtime) {
			Tour tour;
			tour.semi_double_sided_nn_heur(idata, param, randmt);
			tour.calc_tour_cost(idata);
			if (tour.sol_value < best_tour.sol_value) {
				best_tour = tour;
			}
			get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
		}
		get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
		cpu_time.total_s_CPU += (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
	}

	best_tour.calc_tour_cost(idata);
}