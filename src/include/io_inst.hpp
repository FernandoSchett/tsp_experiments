#ifndef io_inst_class
#define io_inst_class

#include "parameters.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <regex>

struct Point {
    int id;
    long double x;
    long double y;
};

class IData {
public:
    std::string instance_name;
    int n_nodes;
    std::string edge_weight_type;
    std::string edge_weight_format;
    std::string edge_data_format;
    std::string node_coord_type;
    std::string display_data_type;
    std::vector<int> nodes;
    std::vector<std::vector<int>> distances;
    std::vector<Point> node_coords;

    void read_input(Parameters& param);
    void build_distance_matrix_for_euc_2D(std::ifstream& file);
};

#endif