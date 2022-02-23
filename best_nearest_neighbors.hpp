// Artificial Intelligence 2021
// AI CUP 2021
// Matteo Alberici
// best_nearest_neighbors.hpp

#ifndef BEST_NEAREST_NEIGHBORS_HPP
#define BEST_NEAREST_NEIGHBORS_HPP

#include <vector>

using namespace std;

// nearest_neighbors_algorithm : first constructive algorithm implemented
vector<float> nearest_neighbors_algorithm(ProblemInstance * _instance, vector<bool> & already_visited_nodes, int starting_node = 0) {
    vector<vector<float> > dist_matrix = _instance->dist_matrix;
    int n = _instance->nPoints;
    int node = starting_node;
    vector<float> tour;
    tour.push_back(node);
    already_visited_nodes[node] = true;
    for (int i = 0; i < n - 1; i++) {
        float minimum_distance = INFINITY;
        float minimum_distance_index = 0;
        for (int new_index = 0; new_index < n; new_index++) {
            if (new_index == i) {
                continue;
            }
            float current_distance = _instance->dist_matrix[tour[tour.size() - 1]][new_index];
            if (current_distance < minimum_distance && already_visited_nodes[new_index] == false) {
                minimum_distance = current_distance;
                minimum_distance_index = new_index;
            }
        }
        already_visited_nodes[minimum_distance_index] = true;
        tour.push_back(minimum_distance_index);
    }
    return tour;
}

// tour_length : computes the length of the tour
int tour_length(vector<float> solution, vector<vector<float> > distance_matrix) {
    int tour_length = 0;
    int first_node = solution[0];
    int tmp_node = first_node;
    // iterator starts from position [1]
    for (int i = 1; i < solution.size(); i++) {
        int dest_node = solution[i];
        tour_length += distance_matrix[tmp_node][dest_node];
        tmp_node = dest_node;
    }
    tour_length += distance_matrix[first_node][tmp_node];
    return tour_length;
}

// best_nearest_neighbors_algorithm : second constructive algorithm implemented
vector<float> best_nearest_neighbors_algorithm(ProblemInstance * instance) {
    vector<float> solution;
    int n = instance->nPoints;
    float min_length = INFINITY;
    for (int i = 0; i < n; i++) {
        vector<bool> already_visited_nodes(n, false);
        // solution returned by the nearest neighbors algorithm
        vector<float> nn = nearest_neighbors_algorithm(instance, already_visited_nodes, i);
        int current_length = tour_length(nn, instance->dist_matrix);
        if (current_length < min_length) {
            solution = nn;
            min_length = current_length;
        }
    }
    return solution;
}

#endif