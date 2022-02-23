// Artificial Intelligence 2021
// AI CUP 2021
// Matteo Alberici
// two_opt.hpp

#ifndef TWO_OPT_HPP
#define TWO_OPT_HPP

#include <algorithm> 
#include <utility>
#include <vector>
#include "ProblemInstance.hpp"

using namespace std;

// step2opt : performs the reversing step of the 2opt optimization algorithm computing the gain
pair<vector<float>, bool> step2opt(vector<float> tsp_sequence, vector<vector<float> > matrix_dist) {
    vector<float> new_tsp_sequence = tsp_sequence;
    bool reversed = false;
    int minimum_gain = 0;
    int best_i = -1;
    int best_j = -1;
    for (int i = 1; i < new_tsp_sequence.size() - 2; i++) {
        for (int j = i + 1; j < new_tsp_sequence.size() - 1; j++) {
            int old_links_len = matrix_dist[new_tsp_sequence[i]][new_tsp_sequence[i - 1]] + matrix_dist[new_tsp_sequence[j]][new_tsp_sequence[j + 1]];
            int changed_links_len = matrix_dist[new_tsp_sequence[j]][new_tsp_sequence[i - 1]] + matrix_dist[new_tsp_sequence[i]][new_tsp_sequence[j + 1]];
            // having a function to compute the gain value slowed down the computation of the solution
            int gain = changed_links_len - old_links_len;
            if (gain < minimum_gain) {
                reversed = true;
                best_i = i;
                best_j = j;
                minimum_gain = gain;
            }
        }
    }
    if (reversed) {
        reverse(new_tsp_sequence.begin() + best_i, new_tsp_sequence.begin() + best_j + 1);
    }
    return make_pair(new_tsp_sequence, reversed);
}

// loop2opt : performs 2opt optiomization algorithm
vector<float> loop2opt(vector<float> solution, ProblemInstance * instance) {
    bool reversed = true;
    vector<float> new_solution = solution;
    while (reversed) {
        pair<vector<float>, bool> step_solution = step2opt(new_solution, instance->dist_matrix);
        new_solution = step_solution.first;
        reversed = step_solution.second;
    }
    return new_solution;
}

#endif