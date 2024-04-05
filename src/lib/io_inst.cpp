#include "io_inst.hpp"

void IData::read_input(Parameters &param)
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

	std::smatch match;

	std::string aux;
	while (file >> aux){
		if (std::regex_match(aux, rgx_name)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->instance_name;
		} else if (std::regex_match(aux, rgx_type)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> aux;
			assert(aux == "TSP");
		} else if (std::regex_match(aux, rgx_dimension)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->n_nodes;
		} else if (std::regex_match(aux, rgx_ewt)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->edge_weight_type;
		} else if (std::regex_match(aux, rgx_ewf)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->edge_weight_format;
		} else if (std::regex_match(aux, rgx_edf)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->edge_data_format;
		} else if (std::regex_match(aux, rgx_ncf)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->node_coord_type;
		} else if (std::regex_match(aux, rgx_ddt)){
			if (!std::regex_search(aux, match, rgx_colon)) file >> aux;
			file >> this->display_data_type;
		} else if (aux == "EOF"){
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