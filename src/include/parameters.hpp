#ifndef parameters_class
#define parameters_class

#define EPSILON 0.000001
#include <string>
#include <random>

class Parameters{
	public:
	char* filename;
	long double alpha;
	int k_best, seed_rand, iterations, maxtime;
	std::string choice_method;

	Parameters(){
		alpha = 0;
		k_best = 2;
		seed_rand = 0;
		choice_method = "greedy"; 
		iterations = 100;
		maxtime = 3600;
	}
};


#endif