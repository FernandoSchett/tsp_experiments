#include "grasp.hpp"

void grasp(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);

	printf("bestsol;currsol;grasp_sol_value;currtime;iteration\n");
	
	best_tour.semi_nn_heur(idata, params, randmt);
	int greedy_sol_value = best_tour.sol_value;
	local_search(best_tour, idata, params, cpu_time);
	printf("%d;%d;%d;%lf;%d\n", best_tour.sol_value, best_tour.sol_value, greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, 1);

	int i = 1;
	
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
	
	CPUTime dummy_time;
	Tour cand_elite_group;
	std::vector<Tour> elite_group;
	printf("bestsol;currsol;grasp_sol_value;currtime;iteration\n");
	
	best_tour.semi_nn_heur(idata, params, randmt);
	int greedy_sol_value = best_tour.sol_value, best_sol_value = best_tour.sol_value;
	local_search(best_tour, idata, params, cpu_time);
	update_elite_group(elite_group, best_tour, params.k_best);
	printf("%d;%d;%d;%lf;%d\n", best_tour.sol_value, best_tour.sol_value, greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, 1);

	int i = 1;
	
	while (!is_stop_criterion_satsfied(params, best_tour.sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i)) {
		Tour tour;
		tour.semi_nn_heur(idata, params, randmt);
		int semi_greedy_sol_value = tour.sol_value;
		local_search(tour, idata, params, dummy_time);

		cand_elite_group = elite_group[randmt() % elite_group.size()];	

		if(params.pr_mode == "f"){
			path_relinking(cand_elite_group, tour, idata, params, dummy_time);
		}else if(params.pr_mode == "b"){
			path_relinking(tour, cand_elite_group, idata, params, dummy_time);
		}else if(params.pr_mode == "bf"){
			path_relinking(cand_elite_group, tour, idata, params, dummy_time);
			path_relinking(tour, cand_elite_group, idata, params, dummy_time);
		}else if(params.pr_mode == "m"){
			path_relinking_mixed(tour, cand_elite_group, idata, params, dummy_time);
		}else{
			printf("ERROR: No PR mode avaliabe.\n");
			exit(0);
		}
		
		update_elite_group(elite_group, tour, params.k_best);
		
		if(best_sol_value > tour.sol_value){
			best_sol_value = tour.sol_value;
		}

		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_CPU_inicial);
		printf("%d;%d;%d;%lf;%d\n", best_sol_value, tour.sol_value, semi_greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i);
		i++;
	}

	
	for(Tour i : elite_group){
		if(i.sol_value < best_tour.sol_value){
			best_tour = i;
		}
	}

	get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
	cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
}

void grasp_prr(Tour& best_tour, IData& idata, Parameters& params, CPUTime& cpu_time, std::mt19937& randmt) {
	get_cpu_time(&cpu_time.s_CPU_inicial, &cpu_time.s_total_inicial);
	get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_total_during);
	
	CPUTime dummy_time;
	Tour cand_elite_group;
	std::vector<Tour> elite_group;
	printf("bestsol;currsol;grasp_sol_value;currtime;iteration\n");
	
	best_tour.semi_nn_heur(idata, params, randmt);
	int greedy_sol_value = best_tour.sol_value, best_sol_value = best_tour.sol_value, last_restart = 0;
	local_search(best_tour, idata, params, cpu_time);
	update_elite_group(elite_group, best_tour, params.k_best);
	printf("%d;%d;%d;%lf;%d\n", best_tour.sol_value, best_tour.sol_value, greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, 1);
	std::cout << params.restart_k << '\n';
	int i = 1;
	
	while (!is_stop_criterion_satsfied(params, best_tour.sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i)) {
		Tour tour;
		tour.semi_nn_heur(idata, params, randmt);
		int semi_greedy_sol_value = tour.sol_value;
		local_search(tour, idata, params, dummy_time);

		cand_elite_group = elite_group[randmt() % elite_group.size()];	

		if(params.pr_mode == "f"){
			path_relinking(cand_elite_group, tour, idata, params, dummy_time);
		}else if(params.pr_mode == "b"){
			path_relinking(tour, cand_elite_group, idata, params, dummy_time);
		}else if(params.pr_mode == "bf"){
			path_relinking(cand_elite_group, tour, idata, params, dummy_time);
			path_relinking(tour, cand_elite_group, idata, params, dummy_time);
		}else if(params.pr_mode == "m"){
			path_relinking_mixed(tour, cand_elite_group, idata, params, dummy_time);
		}else{
			printf("ERROR: No PR mode avaliabe.\n");
			exit(0);
		}
		
		update_elite_group(elite_group, tour, params.k_best);
		
		if(best_sol_value > tour.sol_value){
			best_sol_value = tour.sol_value;
		}

		if((i - last_restart) > params.restart_k){
			elite_group.clear();
			last_restart = i;
		}

		get_cpu_time(&cpu_time.s_CPU_during, &cpu_time.s_CPU_inicial);
		printf("%d;%d;%d;%lf;%d\n", best_sol_value, tour.sol_value, semi_greedy_sol_value, cpu_time.s_CPU_during - cpu_time.s_CPU_inicial, i);
		i++;
	}

	
	for(Tour i : elite_group){
		if(i.sol_value < best_tour.sol_value){
			best_tour = i;
		}
	}

	get_cpu_time(&cpu_time.s_CPU_final, &cpu_time.s_total_final);
	cpu_time.total_s_CPU = (cpu_time.s_CPU_final - cpu_time.s_CPU_inicial);
}

void update_elite_group(std::vector<Tour>& elite_group, Tour& tour, int elite_size){
	//std::cout << "TAMANHO: " << elite_group.size() << '\n';
	//std::cout << "tour valor: " << tour.sol_value << '\n';

	if(elite_group.size() < elite_size){
		if(elite_group.size() == 0){
			elite_group.push_back(tour);
		}else{
			for(Tour i : elite_group){
				if(is_equal(i, tour)){
					return;
				}
			}
			elite_group.push_back(tour);
		}
	}else{
		int least_neighbors = INT_MAX, max_value = INT_MIN, target_it = 0;
		std::list<Tour>::iterator target;
		
		for(int i =0; i != elite_group.size(); i++){
			if(neighborhood_size(tour, elite_group[i]) < least_neighbors){
				least_neighbors = neighborhood_size(tour, elite_group[i]);
				target_it = i;
			}
			if(elite_group[i].sol_value > max_value){
				max_value = elite_group[i].sol_value;
			} 
		}
		//std::cout << "LEAST_VIZINHOS: " << least_neighbors << '\n';
		//std::cout << "max_value: " << max_value << '\n';
		
		if(least_neighbors > 0 && tour.sol_value < max_value){
			//std::cout << "INSERIDO! TROCADO COM "<< elite_group[target_it].sol_value << '\n';

			elite_group[target_it] = tour;
		}
	}
} 


bool is_equal(Tour& tour1, Tour& tour2){
	if(tour1.sol_value != tour2.sol_value){
		return false;
	}
    
    int neighbors = 0; 
    std::list<int>::iterator i = tour1.tour.begin();
    std::list<int>::iterator j = tour2.tour.begin();
    
    while(*j != *i){
        j++;
    }

    while(i != tour1.tour.end()){

        //std::cout << "J: " << *j <<'\n';
        //std::cout << "I: " <<  *i <<'\n';
        //std::cout << '\n';
        if(*j != *i){
			return false;
            //std::cout << "TROCOU:" << neighbors <<'\n';
            //std::cout << *i <<'\n';
            //std::cout << *j <<'\n';
        }
        
        i++;
        j++;
        if(j == tour2.tour.end()){
            //std::cout << "ENTROU AQUI" <<'\n';
            j = tour2.tour.begin();
        }
    }
    //std::cout << "NEIGHBORS: " << neighbors <<'\n';
    //guide_tour.print_tour();
    //inter_sol.print_tour();
    return true;
}
