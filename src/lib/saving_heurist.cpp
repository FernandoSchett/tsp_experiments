#include "tour.hpp"
#include <vector>
#include <algorithm>

#include "tour.hpp"
#include <vector>
#include <algorithm>

void Tour::saving_heur(IData& inst, Parameters& params) {
    struct Savings {
        int i, j;
        double saving;
    };


    std::vector<std::vector<int>> indicador(inst.n_nodes + 1, std::vector<int>(inst.n_nodes + 1, 0));
    for (int i = 1; i <= inst.n_nodes; i++) {
        indicador[1][i] = 2;
    }

    // Calcula economias para cada par de nós i e j
    std::vector<Savings> savingsList;
    for (int i = 2; i <= inst.n_nodes; i++) {
        for (int j = i + 1; j <= inst.n_nodes; j++) {
            double s = inst.distances[1][i] + inst.distances[1][j] - inst.distances[i][j];
            savingsList.push_back({i, j, s});
        }
    }

    // Ordena as economias em ordem decrescente
    std::sort(savingsList.begin(), savingsList.end(), [](const Savings& a, const Savings& b) {
        return a.saving > b.saving;
    });

    for (auto& save : savingsList) {
        if (indicador[1][save.i] == 2 && indicador[1][save.j] > 0) {
        
        }
    }
    
    
    
    // Criar a rota inicial com todos os nós ligados ao depósito
    std::list<int> tour;
    for (int i = 1; i <= inst.n_nodes; i++) {
        tour.push_back(i);
        tour.push_back(1);
    }

    // Aplicar as economias para fundir rotas
    for (auto& save : savingsList) {
        if (!visited[save.i] && !visited[save.j]) {
            // Encontrar posições no tour para tentar fundir
            auto it_i = std::find(tour.begin(), tour.end(), save.i);
            auto it_j = std::find(tour.begin(), tour.end(), save.j);

            if (it_i != tour.end() && it_j != tour.end() && (++it_i == --it_j)) {
                visited[save.i] = visited[save.j] = true;
                tour.erase(it_i);
            }
        }
    }

    // Limpa a lista de tour e insere elementos de forma eficiente
    this->tour.clear();
    for (auto& node : tour) {
        if (node != 1 || this->tour.empty() || this->tour.front() != 1) {
            this->tour.push_back(node);
        }
    }

    // Calcula o valor da solução
    this->sol_value = 0;
    std::list<int>::iterator prev = this->tour.begin();
    std::list<int>::iterator curr = std::next(prev);
    while (curr != this->tour.end()) {
        this->sol_value += inst.distances[*prev][*curr];
        prev = curr++;
    }
    this->sol_value += inst.distances[*prev][this->tour.front()];
}
