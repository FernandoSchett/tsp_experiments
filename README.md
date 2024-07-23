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

This repository contains the implementation of various algorithms designed to tackle the Traveling Salesman Problem (TSP). The project is part of the evaluation for the Topics in Computational Systems III course at the Federal University of Bahia (UFBA), supervised by Professor Celso da Cruz Carneiro Ribeiro, conducted in the first semester of 2023. The repository includes the implementation of adaptive greedy heuristics, multi-start procedures, and local search algorithms. The source code and datasets[2] used for testing are provided to facilitate further research and replication of results.

## Summary 📝:

## Resourses 🧑‍🔬:

- TSP instances and solutions **reader**; 
- **Constructive Heuristics:** Nearest Neighbor (Greedy and Semi-Greedy, alpha and k_best);
- **Local Search:** Two-opt Best Improvement, First Improvement, Candidade lists and Circular Search;
- **GRASP Heuristic**, and it's variations;
- **Path Relinking** with restart;
- **Executions Scripts** avaliable at ```./scripts/```;
- **Experiments Analysis and graphs** at ```./results_tsp_project.pdf``` ; 
- **Logs generators**;

## How to run it 🏃:

First, clone this repository. After that, yout can use some of scripts avaliable at ```./scripts/``` or simply type:

    make all
    ./TSP [options]

## UML‍ 💬:

Heres the UML that represents how the application works with their classes.

```mermaid
classDiagram

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

- [Tool](http:link.com). 
- 
- 

For installing some tools more quickly, you can run the following command at terminal, inside the clonned repository:

    sh ./dependencies/install_tools.sh
	
## How to contribute 🫂:

Feel free to create a new branch, fork the project, create a new Issue or make a pull request contact one of us to develop at <app_name>.

## Licence 📜:

[Apache V2](https://choosealicense.com/licenses/apache-2.0/)


## References 📙:
	
[1] [Karp 1972] Karp, R. M. (1972). Reducibility among Combinatorial Problems, page
85–103. Springer US.
	
[2] [Reinelt 1991] Reinelt, G. (1991). TSPLIB–a traveling salesman problem library. ORSA
Journal on Computing, 3(4):376–384.

[3] [Resende and Ribeiro 2016] Resende, M. G. and Ribeiro, C. C. (2016). Optimization by
GRASP: Greedy Randomized Adaptive Search Procedures. Springer New York.
