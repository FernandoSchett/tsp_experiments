#ifndef io_inst_class
#define io_inst_class

#include "parameters.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

class IData{
public:
    std::string instance_name;
    std::vector<int> nodes;
    std::vector<std::vector<long double>> distances;

    void read_input(Parameters& param);
};

#endif