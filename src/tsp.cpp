#include <random>
std::mt19937 randmt;
#include "parameters.hpp"
#include "io_inst.hpp"
#include "get_sys_time.hpp"
#include "tour.hpp"
#include "choice_method.hpp"
#include <iostream>
#include <iomanip>
#include <getopt.h>
#include <string>
#include <filesystem>

void show_help(const char* name) {
	fprintf(stderr, "\
			[uso] %s <opcoes>\n\
			-h,		--help				show this screen.\n\
			-s, 	--seed=SEED 		set seed for randomized selection.\n\
			-k, 	--k_best=K_BEST		set k for cardinality-based randomization.\n\
			-a, 	--alpha=ALPHA 	    set alpha for quality-based randomization.\n\
			-f,  	--filename     		set filename.\n\
			-c,  	--choice_method     set choice_method.\n\
			-m, 	--scheme 			set scheme for semi-greedy algorithm.\n\
			-t, 	--maxtime 			set maxtime in seconds.\n\
			-i,		--iterations		set multi-start number of iterations.\n", name);
	exit(-1);
}

void read_args(const int argc, char* argv[], Parameters& param) {
	int opt;
	/*
		https://daemoniolabs.wordpress.com/2011/10/07/usando-com-as-funcoes-getopt-e-getopt_long-em-c/
		https://linux.die.net/man/3/getopt_long
	*/
	const option options[] = {
		{"help"				, no_argument       , 0 , 'h' },
		{"seed"				, required_argument , 0 , 's' },
		{"k_best"			, required_argument , 0 , 'k' },
		{"alpha"			, required_argument , 0 , 'a' },
		{"filename"			, required_argument , 0 , 'f' },
		{"iterations"		, required_argument , 0 , 'i' },
		{"maxtime"			, required_argument , 0 , 'i' },
		{"choice_method"	, required_argument , 0 , 'c' },
		{"scheme"			, required_argument , 0 , 'm' },
		{0       			, 0 				, 0	,  0  },
	};

	if (argc < 2) {
		show_help(argv[0]);
	}

	while ((opt = getopt_long(argc, argv, "hs:k:a:f:c:m:i:t:", options, NULL)) > 0) {
		switch (opt) {
		case 'h': /* -h ou --help */
			show_help(argv[0]);
			break;
		case 's': /* -s ou --seed */
			param.seed_rand = std::atoi(optarg);
			break;
		case 'k': /* -k ou --k_best */
			param.k_best = std::atoi(optarg);
			break;
		case 'a': /* -a ou --alpha */
			param.alpha = std::stold(optarg);
			break;
		case 'f': /* -f ou --filename */
			param.filename = optarg;
			break;
		case 'c': /* -c ou --choice_method */
			param.choice_method = optarg;
			break;
		case 'm': /* -m ou --scheme */
			param.scheme = optarg;
			break;
		case 'i': /* -i ou --iterations */
			param.iterations = std::atoi(optarg);
			break;
		case 't': /* -t ou --maxtime */
			param.maxtime = std::atoi(optarg);
			break;
		default:
			fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt);
			exit(-1);
		}
	}
}

int32_t main(int argc, char* argv[]) {
	// std::ios::sync_with_stdio(false); std::cin.tie(0);

	Parameters param;
	IData idata;
	CPUTime cpu_time;

	read_args(argc, argv, param);

	std::cout << param.filename << std::endl;

	randmt = std::mt19937(param.seed_rand);

	idata.read_input(param);

	Tour best_tour;
	run_choice_method(best_tour, idata, param, cpu_time, randmt);

	std::ofstream file;
	file.open("./results/time_result.txt", std::ofstream::out | std::ofstream::app);

	if (!file)
		exit(1);

	file << idata.instance_name << ';' << param.choice_method << ';' << best_tour.sol_value << ';' << param.alpha << ';' << param.k_best << ';' << param.scheme << ';' << param.iterations << ';';
	file << std::setprecision(6) << cpu_time.total_s_CPU << '\n';
	file.close();

	

	if (best_tour.is_tour_valid(idata)) {
		best_tour.print_tour();
		printf("Valid tour! :D\n");
		std::string caminho;

		if(param.scheme == "alpha"){
			caminho = "benchmark/solutions/" + param.choice_method + "_" + param.scheme + "_" + std::to_string(param.alpha);
		}else if(param.scheme == "k_best"){
			
			caminho = "benchmark/solutions/" + param.choice_method + "_" + param.scheme + "_" + std::to_string(param.k_best);
		}else{
			
			caminho = "benchmark/solutions/" + param.choice_method;
		}

		std::filesystem::path caminho_dir = caminho;
		
		std::filesystem::create_directory(caminho_dir);
		std::ofstream ac_solution;
		ac_solution.open(caminho + "/" + idata.instance_name + ".txt");
		if (!file)
			exit(1);

		ac_solution << "TOUR:\n";
		for (int node : best_tour.tour) {
			ac_solution << " " << node;
		}
		ac_solution << "\n";
		ac_solution << "COST = " << best_tour.sol_value << "\n";
	
	}else {
		printf("Invalid tour... :(\n");
	}
	return 0;
}
