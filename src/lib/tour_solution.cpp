#include "tour.hpp"

void Tour::calc_tour_cost(IData& inst) {
    this->sol_value = 0;
    std::list<int>::iterator prev = this->tour.begin();
    std::list<int>::iterator curr = this->tour.begin(); curr++;
    while (curr != this->tour.end()) {
        this->sol_value += inst.dist(inst.node_coords[*prev], inst.node_coords[*curr]);
        prev++;
        curr++;
    }
    this->sol_value += inst.dist(inst.node_coords[*prev], inst.node_coords[this->tour.front()]);
}

bool Tour::is_tour_valid(IData& inst) {
    
    if (this->tour.size() != inst.n_nodes) {
        return false;
    }
    std::vector<int> visited(inst.n_nodes + 1, 0);
    for (int node : this->tour) {
        visited[node]++;
        if (visited[node] > 1) {
            return false;
        }
    }

    for (int i = 1; i < visited.size(); i++) {
        if (visited[i] != 1) {
            return false;
        }
    }
    
    int cost = 0;
    std::list<int>::iterator prev = this->tour.begin();
    std::list<int>::iterator curr = this->tour.begin(); curr++;

    while (curr != this->tour.end()) {
        cost += inst.dist(inst.node_coords[*prev], inst.node_coords[*curr]);
        prev++;
        curr++;
    }
    cost += inst.dist(inst.node_coords[*prev], inst.node_coords[this->tour.front()]);

    if (cost != this->sol_value){
        printf("Sol value is incorrect: expected (%d) - calculated (%d)", cost, this->sol_value);
        return false;
    }
    return true;
}

void Tour::print_tour() {
    printf("TOUR:\n");
    for (int node : this->tour) {
        printf(" %d", node);
    }
    printf("\n");
    printf("COST = %d\n", this->sol_value);
}

void Tour::save_time_result(IData& idata, Parameters& params, CPUTime& cpu_time){
    std::filesystem::create_directory("./results/" + params.path_to);
	std::ofstream file;
	file.open("./results/" + params.path_to + "/time_result.txt", std::ofstream::out | std::ofstream::app);

	if (!file)
		exit(1);

	file << idata.instance_name << ';' << params.choice_method << ';' << this->sol_value << ';' << params.alpha << ';' << params.k_best << ';' << params.scheme << ';' << params.iterations << ';' << params.local_search << ';';
	file << std::setprecision(6) << cpu_time.total_s_CPU << '\n';
	file.close();
}

void Tour::save_solution_to_file(IData& idata, Parameters& params) {
    std::filesystem::create_directory("benchmark/solutions/" + params.path_to);
    std::ofstream ac_solution;
    ac_solution.open("benchmark/solutions/" + params.path_to + "/" + idata.instance_name + ".txt");
    if (!ac_solution){
        printf("The solution file was not opened, thus solution couldn't be written into a file.\n");
        exit(1);
    }

    ac_solution << "TOUR:\n";
    for (int node : this->tour) {
        ac_solution << " " << node;
    }
    ac_solution << "\n";
    ac_solution << "COST = " << this->sol_value << "\n";
    ac_solution.close();
}

void Tour::read_solution_file(IData& idata, Parameters& params) {
    std::ifstream ac_solution;
    ac_solution.open("benchmark/solutions/" + params.path_load_solution + "/" + idata.instance_name + ".txt", std::ifstream::in);
    if (!ac_solution){
        printf("The solution file was not opened, thus solution file couldn't be read.\n");
        // this->nn_heur(idata, params);
        // this->calc_tour_cost(idata);
        // return;
        exit(1);
    }

    this->tour.clear();

    std::string aux;
    ac_solution >> aux;
    assert(aux == "TOUR:");
    while (ac_solution >> aux && aux != "COST") {
        this->tour.push_back(std::stoi(aux));
    }
    ac_solution >> aux;
    assert(aux == "=");
    ac_solution >> this->sol_value;
    ac_solution.close();
}