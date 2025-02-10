/*
 * -----------------------------------------------------------------------------
 * File Name:          tsp.cpp
 * Authors:            Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
 * Last Modified Date: 22/07/2024
 * Purpose:            Read a TSP instance and execute a heuristic on the traveling salesman problem, saving the solution to a file.
 * How to Compile: make all
 * How to Run: ./tsp [options]
 * 
 * Notes:
 * - Check the README.md and ./scripts files for more information.          
 * -----------------------------------------------------------------------------
 */

 #include <random>
 #include "parameters.hpp"
 #include "io_inst.hpp"
 #include "get_sys_time.hpp"
 #include "tour.hpp"
 #include "choice_method.hpp"
 #include <iostream>
 #include <iomanip>
 #include <getopt.h>
 #include <string>
 
 std::mt19937 randmt;
 
 void show_help(const char* name) {
	 fprintf(stderr, "\
			 [uso] %s <opcoes>\n\
			 -h,      --help               show this screen.\n\
			 -r       --local_search       set local search. \n\
			 -s,      --seed=SEED          set seed for randomized selection.\n\
			 -k,      --k_best=K_BEST      set k for cardinality-based randomization.\n\
			 -a,      --alpha=ALPHA        set alpha for quality-based randomization.\n\
			 -f,      --filename           set filename.\n\
			 -c,      --choice_method      set choice_method.\n\
			 -m,      --scheme             set scheme for algorithms.\n\
			 -p,      --stop_crit          set stop criterion for choice_method.\n\
			 -l,      --path_load_sol      set path to load solution.\n\
			 -t,      --maxtime            set maxtime in seconds.\n\
			 -i,      --iterations         set max number of iterations.\n\
			 -g,      --pr_mode            set path relinking mode.\n\
			 -e,      --restart_k          set restart iterations for path relinking.\n\
			 -o,      --look4              set look4 value.\n\
			 -n,      --n_particles        set number of particles.\n\
			 -j,      --n_threads          set number of threads.\n", name);
	 exit(-1);
 }
 
 void read_args(const int argc, char* argv[], Parameters& param) {
	 int opt;
	 const option options[] = {
		 {"help"          , no_argument       , 0 , 'h' },
		 {"local_search"  , required_argument , 0 , 'r' },
		 {"seed"          , required_argument , 0 , 's' },
		 {"k_best"        , required_argument , 0 , 'k' },
		 {"alpha"         , required_argument , 0 , 'a' },
		 {"filename"      , required_argument , 0 , 'f' },
		 {"iterations"    , required_argument , 0 , 'i' },
		 {"maxtime"       , required_argument , 0 , 't' },
		 {"choice_method", required_argument , 0 , 'c' },
		 {"scheme"        , required_argument , 0 , 'm' },
		 {"stop_crit"     , required_argument , 0 , 'p' },
		 {"path_load_sol" , required_argument , 0 , 'l' },
		 {"look4"         , required_argument , 0 , 'o' },
		 {"pr_mode"       , required_argument , 0 , 'g' },
		 {"restart_k"     , required_argument , 0 , 'e' },
		 {"n_particles"   , required_argument , 0 , 'n' },
		 {"n_threads"     , required_argument , 0 , 'j' },
		 {0               , 0                 , 0 ,  0  }
	 };
 
	 if (argc < 2) {
		 show_help(argv[0]);
	 }
 
	 while ((opt = getopt_long(argc, argv, "hs:k:r:a:f:c:m:p:i:t:l:o:g:e:n:j:", options, NULL)) > 0) {
		 switch (opt) {
			 case 'h':
				 show_help(argv[0]);
				 break;
			 case 's':
				 param.seed_rand = std::atoi(optarg);
				 break;
			 case 'k':
				 param.k_best = std::atoi(optarg);
				 break;
			 case 'a':
				 param.alpha = std::stold(optarg);
				 break;
			 case 'f':
				 param.filename = optarg;
				 break;
			 case 'c':
				 param.choice_method = optarg;
				 break;
			 case 'm':
				 param.scheme = optarg;
				 break;
			 case 'p':
				 param.stop_criterion = optarg;
				 break;
			 case 'i':
				 param.iterations = std::atoi(optarg);
				 break;
			 case 't':
				 param.maxtime = std::atoi(optarg);
				 break;
			 case 'l':
				 param.path_load_solution = optarg;
				 break;
			 case 'r':
				 param.local_search = optarg;
				 break;
			 case 'o':
				 param.look4 = std::atoi(optarg);
				 break;
			 case 'g':
				 param.pr_mode = optarg;
				 break;
			 case 'e':
				 param.restart_k = std::atoi(optarg);
				 break;
			 case 'n':
				 param.n_particles = std::atoi(optarg);
				 break;
			 case 'j':
				 param.n_threads = std::atoi(optarg);
				 break;
			 default:
				 fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt);
				 exit(-1);
		 }
	 }
	 param.build_path_to();
 }
 
 int32_t main(int argc, char* argv[]) {
	 Parameters param;
	 IData idata;
	 CPUTime cpu_time;
 
	 read_args(argc, argv, param);
 
	 std::cout <<  param.filename << std::endl;
 
	 randmt = std::mt19937(param.seed_rand);
 
	 idata.read_input(param);
 
	 Tour best_tour;
	 run_choice_method(best_tour, idata, param, cpu_time, randmt);
 
	 best_tour.save_time_result(idata, param, cpu_time);
 
	 if (best_tour.is_tour_valid(idata)) {
		 best_tour.print_tour();
		 printf("Valid tour! :D\n");
		 best_tour.save_solution_to_file(idata, param);
	 } else {
		 printf("Invalid tour... :(\n");
	 }
	 return 0;
 }
 