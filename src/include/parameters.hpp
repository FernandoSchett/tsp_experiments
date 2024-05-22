#ifndef parameters_class
#define parameters_class

#define EPSILON 0.000001
#include <string>
#include <random>

class Parameters {
public:
	char* filename;
	long double alpha;
	int k_best, seed_rand, iterations, maxtime, look4;
	std::string scheme;
	std::string choice_method;
	std::string stop_criterion; // "iter" or "time"
	std::string path_to;
	std::string path_load_solution;
	std::string local_search;

	void build_path_to();
};


#endif