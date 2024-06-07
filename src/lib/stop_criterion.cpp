#include "stop_criterion.hpp"

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