// Artificial Intelligence 2021
// AI CUP 2021
// Matteo Alberici
// SolverTSP.hpp

#ifndef SOLVERTSP_HPP
#define SOLVERTSP_HPP

#include <ctime>
#include <vector>
#include "best_nearest_neighbors.hpp"
#include "ProblemInstance.hpp"
#include "two_opt.hpp"

using namespace std;

class SolverTSP {
public:
    float duration;
    int found_length;
    bool solved;
    ProblemInstance * problem_instance;
    float gap;
    vector<float> solution;

    // SolverTSP : contructor function to initialize a SolverTSP object
    SolverTSP(ProblemInstance * problem) {
        this->duration = 0;
        this->found_length = 0;
        this->solved = false;
        this->gap = 0;
        this->problem_instance = problem;
        this->solution = compute_solution();
    }

    // compute_solution : solves a problem with the given algorithms
    vector<float> compute_solution() {
        clock_t start = clock();
        printf("\n### solving problem with ['bnn', 'two_opt'] ####\n");
        vector<float> solution = best_nearest_neighbors_algorithm(this->problem_instance);
        solution = loop2opt(solution, this->problem_instance);
        if (!check_if_solution_is_valid(solution)) {
            printf("Error the solution is not valid\n");
            exit(1);
        }
        this->duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        this->found_length = tour_length(solution, this->problem_instance->dist_matrix);
        this->solved = true;
        printf("best solution %f\nwith len %d\nwith a total time of %f seconds\n", this->problem_instance->best_sol, this->found_length, this->duration);
        this->gap = _gap();
        printf("solution found has a %f%% gap\n", this->gap);
        return solution;
    }

    // check_if_solution_is_valid : checks the solution's validity
    bool check_if_solution_is_valid(vector<float> solution) {
        int count = 0;
        for (int i = 0; i < this->problem_instance->nPoints; i++) {
            for (vector<float>::iterator it = solution.begin(); it != solution.end(); it++) {
                float to_check = float(i);
                if (*it == to_check) {
                    count++;
                }
            }
        }
        if (this->problem_instance->nPoints == count) {
            return true;
        }
        return false;
    }

    // _gap : computes the gap value
    float _gap() {
        return float(this->found_length - this->problem_instance->best_sol) / float(this->problem_instance->best_sol) * 100.0;
    }
};

#endif
