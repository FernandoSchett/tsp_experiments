#ifndef parameters_class
#define parameters_class

#define EPSILON 0.000001
#include <string>
#include <random>

class Parameters {
public:
	char* filename;
	long double alpha;
	int k_best, seed_rand, iterations, maxtime;
	std::string scheme;
	std::string choice_method;
	std::string stop_criterion; // "iter" or "time"
	std::string path_to;

	void build_path_to();
};


#endif