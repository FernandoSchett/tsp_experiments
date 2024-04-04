#include "io_inst.hpp"

void IData::read_input(Parameters &param)
{
    std::ifstream file;
    file.open(param.filename);
    if (!file)
        exit(1);

    std::string aux;
    file >> aux;
    assert(aux == "NAME:");
    file >> this->instance_name;

    file >> aux;
    assert(aux == "TYPE:");
    file >> aux;
    assert(aux == "TSP");

    while (true){
        file >> aux;
        if (aux == "DIMENSION:"){
            assert(aux == "DIMENSION:");
            file >> this->n_nodes;
        } else if (aux == "EDGE_WEIGHT_TYPE:"){
            assert(aux == "EDGE_WEIGHT_TYPE:");
            file >> this->edge_weight_type;
        } else if (aux == "EDGE_WEIGHT_FORMAT:"){
            assert(aux == "EDGE_WEIGHT_FORMAT:");
            file >> this->edge_weight_format;
        } else if (aux == "EDGE_DATA_FORMAT:"){
            assert(aux == "EDGE_DATA_FORMAT:");
            file >> this->edge_data_format;
        } else if (aux == "NODE_COORD_TYPE:"){
            assert(aux == "NODE_COORD_TYPE:");
            file >> this->node_coord_type;
        } else if (aux == "DISPLAY_DATA_TYPE:"){
            assert(aux == "DISPLAY_DATA_TYPE:");
            file >> this->display_data_type;
        } else if( aux == "EOF"){
            break;
        }
    }

    std::cout << this->n_nodes << std::endl;
    std::cout << this->edge_weight_type << std::endl;
    std::cout << this->edge_weight_format << std::endl;
    std::cout << this->edge_data_format << std::endl;
    std::cout << this->node_coord_type << std::endl;
    std::cout << this->display_data_type << std::endl;

    file.close();
}