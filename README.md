<h1 align="center">🧑‍💼 TSP Experiments 🧑‍💼</h1>

<div align="center">
	<a href="link_for_webite">
	<img height = "250em" src = "https://github.com/FernandoSchett/tsp_experiments/assets/80331486/fca392e2-8956-4971-a10d-4c1858d43a5d" />
    </a>
</div>

## Developed by 💻:
- [Fernando Schettini](https://linktr.ee/fernandoschett).
- [Vitor Alves Barbosa Schettini](https://github.com/MrAlves17).

## Special thanks to 🥰:
- [Celso C. Ribeiro](http://profs.ic.uff.br/~celso/), our advisees in this work.

## About 🤔:

This repository contains the implementation of various algorithms designed to tackle the Traveling Salesman Problem (TSP). The project is part of the evaluation for the Topics in Computational Systems III course at the Federal University of Bahia (UFBA), supervised by Professor Celso da Cruz Carneiro Ribeiro, conducted in the first semester of 2023. The repository includes the implementation of adaptive greedy heuristics, multi-start procedures, local search  and path relinking algorithms.

The source code and datasets used for testing are provided to facilitate further research and replication of results (avaliable at [here]()). You can also read `./results_tsp_project.pdf` to get experiment analysis and graphs, or check this [Overleaf link](https://www.overleaf.com/read/yzgxqkwwzkwt#623679) for the online version. For a quicker approach, check out our YouTube presentation available at this [link]().

## Resourses 🧑‍🔬:

- TSP instances and solutions **reader**; 
- **Constructive Heuristics:** Nearest Neighbor and Double-Sided Nearest Neighbor (Greedy and Semi-Greedy, alpha and k_best);
- **Local Search** (Two-opt Best Improvement, First Improvement, Candidade lists and Circular Search);
- **Path Relinking** with restart;
- **GRASP Heuristic** (GRASP, GRASP + Path Relinking and GRASP + Path Relinking + Restart);
- **Executions Test Scripts**;
- **Experiments Analysis and graphs** at `./results_tsp_project.pdf`; 
- **Logs generators**.

## Repo Overview 📝:

- `./benchmarck/` contains all instances (data) and serves as the log and solution folder.
- `./build/` contains the build files;
- `./results/` contains the final results at each `./src/tsp.cpp` execution;
- `./src/` contains all implemented code: `./src/lib/` for functions, `./src/include/` for headers, and `./src/tsp.cpp` as the main script;
- `./scripts/` contains the scripts used to run all experiments and gather data;
- `./tttplots/` contains the scripts used for creating time-to-target graphs;
- `./results_tsp_project.pdf` is the final document with all experiment results and TSP analysis.

## How to run it 🏃:

First, clone this repository. After that, yout can use some of scripts avaliable at ```./scripts/``` or simply type:
    
    make all
    ./TSP [options]

## UML‍ 💬:

Heres the UML that represents how the application works with their classes.

```mermaid
classDiagram

class Point {
    int id
    long double x
    long double y
}

class Parameters {
    char* filename
    long double alpha
    int k_best
    int seed_rand
    int iterations
    int maxtime
    int look4
    int restart_k
    std::string scheme
    std::string choice_method
    std::string stop_criterion
    std::string path_to
    std::string path_load_solution
    std::string local_search
    std::string pr_mode

    void build_path_to()
}

class IData {
    std::string instance_name
    int n_nodes
    std::string edge_weight_type
    std::string edge_weight_format
    std::string edge_data_format
    std::string node_coord_type
    std::string display_data_type
    std::vector~int~ nodes
    std::vector~std::vector<int>~ distances
    std::vector~Point~ node_coords

    void read_input(Parameters& param)
    int dist(Point p_i, Point p_j)
    void read_node_coords(std::ifstream& file)
    void read_distance_matrix_for_explicit(std::ifstream& file)
    void read_full_matrix(std::ifstream& file)
    void read_upper_row(std::ifstream& file)
    void read_upper_diag_row(std::ifstream& file)
    void read_lower_diag_row(std::ifstream& file)
    void print_distance_matrix()
}

class Candidate {
    int node_orig
    int node
    int dist
}

class Candidate_ls {
    int delta
    std::list~int~::iterator j
    std::list~int~::iterator l
    std::list~int~::iterator i
    std::list~int~::iterator k
    int val_i
    int val_j
    int val_k
    int val_l
}

class Tour {
    std::list~int~ tour
    int sol_value

    void double_sided_nn_heur(IData& inst, Parameters& params)
    void semi_double_sided_nn_heur(IData& inst, Parameters& params, std::mt19937& randmt)
    void nn_heur(IData& inst, Parameters& params)
    void semi_nn_heur(IData& inst, Parameters& params, std::mt19937& randmt)
    void two_opt_first_imprv(IData& inst, Parameters& params, CPUTime& cpu_time)
    void two_opt_best_imprv(IData& inst, Parameters& params, CPUTime& cpu_time)
    void two_opt_best_imprv_cand_list(IData& inst, Parameters& params, CPUTime& cpu_time)
    std::list~Candidate_ls~ get_candidate_list(IData& inst)
    void two_opt_first_imprv_circ_search(IData& inst, Parameters& params, CPUTime& cpu_time)
    std::pair~std::list~int~::iterator, std::list~int~::iterator~ search_neighbors(IData& inst, bool& improvement, std::list~int~::iterator& init_i, std::list~int~::iterator& init_k)
    void calc_tour_cost(IData& inst)
    bool is_tour_valid(IData& inst)
    void print_tour()
    void save_time_result(IData& idata, Parameters& params, CPUTime& cpu_time)
    void save_solution_to_file(IData& idata, Parameters& params)
    void read_solution_file(IData& idata, Parameters& params)
}

IData --> Point
Tour --> IData
Tour --> Parameters
Candidate_ls --> Tour


```

<h4 align="center">Figure 2 - <app_name> UML.</h4>

## Logic Model 🧮:

Here's the logic model that represents how the code works with their classes.

<div align="center">
	<a href="">
	<img height = "250em" src = "https://github.com/FernandoSchett/github_readme_template/assets/80331486/4e4d24ee-efce-41d9-873b-3ececaf1cdd5" />
    </a>
</div>
<h4 align="center">Figure 3 - Logic Model.</h4>

### Tools Used 🛠️: 

- [GNUPLOT](http://www.gnuplot.info/);
- [VS CODE](https://code.visualstudio.com/);
- [Overleaf](https://pt.overleaf.com/).
	
## How to contribute 🫂:

Feel free to create a new branch, fork the project, create a new Issue or make a pull request contact one of us to develop at tsp_project.

## Licence 📜:

[Apache V2](https://choosealicense.com/licenses/apache-2.0/)

## References 📙:
	
[1] [Karp 1972] Karp, R. M. (1972). Reducibility among Combinatorial Problems, page
85–103. Springer US.
	
[2] [Reinelt 1991] Reinelt, G. (1991). TSPLIB–a traveling salesman problem library. ORSA
Journal on Computing, 3(4):376–384.

[3] [Resende and Ribeiro 2016] Resende, M. G. and Ribeiro, C. C. (2016). Optimization by
GRASP: Greedy Randomized Adaptive Search Procedures. Springer New York.
