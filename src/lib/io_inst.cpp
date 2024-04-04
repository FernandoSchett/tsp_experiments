#include "io_inst.hpp"

void IData::read_input(Parameters& param) {
	std::ifstream file;
	file.open(param.filename);
	if (!file) exit(1);

	std::string aux;
    file >> aux;
	assert(aux == "NAME:");
	file >> this->instance_name;
    std::cout << this->instance_name << std::endl;
		
	file.close();
}