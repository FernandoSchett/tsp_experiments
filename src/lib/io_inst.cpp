#include "io_inst.hpp"

void IData::read_input(Parameters& param)
{
	std::ifstream file;
	file.open(param.filename);
	if (!file)
		exit(1);

	std::regex rgx_name("\\NAME[:]*");
	std::regex rgx_type("\\TYPE[:]*");
	std::regex rgx_dimension("\\DIMENSION[:]*");
	std::regex rgx_ewt("\\EDGE_WEIGHT_TYPE[:]*");
	std::regex rgx_ewf("\\EDGE_WEIGHT_FORMAT[:]*");
	std::regex rgx_edf("\\EDGE_DATA_FORMAT[:]*");
	std::regex rgx_ncf("\\NODE_COORD_TYPE[:]*");
	std::regex rgx_ddt("\\DISPLAY_DATA_TYPE[:]*");
	std::regex rgx_colon("\\:");
	std::regex rgx_ncs("\\NODE_COORD_SECTION[:]*");

	std::smatch match;

	std::string aux;
	while (file >> aux) {
		if (std::regex_match(aux, rgx_name)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->instance_name;
		}
		else if (std::regex_match(aux, rgx_type)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> aux;
			assert(aux == "TSP");
		}
		else if (std::regex_match(aux, rgx_dimension)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->n_nodes;
		}
		else if (std::regex_match(aux, rgx_ewt)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->edge_weight_type;
		}
		else if (std::regex_match(aux, rgx_ewf)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->edge_weight_format;
		}
		else if (std::regex_match(aux, rgx_edf)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->edge_data_format;
		}
		else if (std::regex_match(aux, rgx_ncf)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->node_coord_type;
		}
		else if (std::regex_match(aux, rgx_ddt)) {
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->display_data_type;
		}
		else if (std::regex_match(aux, rgx_ncs)) {
			if (this->edge_weight_type == "EUC_2D") {
				this->build_distance_matrix_for_euc_2D(file);
			}
			file >> this->display_data_type;
		}
		else if (aux == "EOF") {
			break;
		}
	}

	std::cout << "instance_name: " << this->instance_name << std::endl;
	std::cout << "n_nodes: " << this->n_nodes << std::endl;
	std::cout << "edge_weight_type: " << this->edge_weight_type << std::endl;
	std::cout << "edge_weight_format: " << this->edge_weight_format << std::endl;
	std::cout << "edge_data_format: " << this->edge_data_format << std::endl;
	std::cout << "node_coord_type: " << this->node_coord_type << std::endl;
	std::cout << "display_data_type: " << this->display_data_type << std::endl;

	file.close();
}

int euc_dist(Point p1, Point p2) {
	long double xd = p1.x - p2.x;
	long double yd = p1.y - p2.y;
	return int(sqrt(xd * xd + yd * yd) + 0.5);
}

void IData::build_distance_matrix_for_euc_2D(std::ifstream& file) {
	std::string aux;
	Point p; p.x = p.y = p.id = 0;
	this->node_coords.push_back(p);
	while (file >> aux) {
		if (aux == "EOF") {
			break;
		}
		p.id = stoi(aux);

		file >> p.x >> p.y;
		printf("%d %.10Lf %.10Lf\n", p.id, p.x, p.y);
		this->node_coords.push_back(p);
	}

	this->distances.resize(this->n_nodes + 1, std::vector<int>(this->n_nodes + 1, 0));
	for (int i = 1; i <= this->n_nodes; i++) {
		this->distances[i][i] = 0;
		for (int j = i + 1; j <= this->n_nodes; j++) {
			int dij = euc_dist(this->node_coords[i], this->node_coords[j]);
			this->distances[i][j] = dij;
			this->distances[j][i] = dij;
		}
	}

}