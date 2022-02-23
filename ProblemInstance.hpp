// Artificial Intelligence 2021
// AI CUP 2021
// Matteo Alberici
// ProblemInstance.hpp

#ifndef PROBLEMINSTANCE_HPP
#define PROBLEMINSTANCE_HPP

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class ProblemInstance {
public:
    string name_stp;
    vector<vector<float> > dist_matrix;
    vector<string> lines;
    string name;
    int nPoints;
    float best_sol;
    vector<vector<float> > points;

    // ProblemInstance : contructor function to initialize a ProblemInstance object
    ProblemInstance(string name_stp) {
        this->name_stp = name_stp;
        // Reading raw data from files
        ifstream data(name_stp);
        string current_line;
        vector<string> lines_vector;
        while (getline(data, current_line)) {
            lines_vector.push_back(current_line);
        }
        this->lines = lines_vector;
        // Store metadata set information from lines: the name of the problem
        this->name = string_split(lines[0], " : ")[1];
        // Store metadata set information from lines: the number of points in the instance
        this->nPoints = stoi(string_split(lines[3], " : ")[1]);
        // Store metadata set information from lines: the lenght of the best solution
        this->best_sol = stof(string_split(lines[5], " : ")[1]);
        // Data points
        vector<vector<float> > data_points(this->nPoints, vector<float>(3));
        for (int i = 7; i < this->nPoints + 7; i++) {
            data_points[i - 7][0] = stof(string_split(lines[i], " ")[0]);
            data_points[i - 7][1] = stof(string_split(lines[i], " ")[1]);
            data_points[i - 7][2] = stof(string_split(lines[i], " ")[2]);
        }
        this->points = data_points;
        // Distance matrix
        this->dist_matrix = create_dist_matrix(this->points, this->nPoints);
    }

    // print_info : prints the details of the problem
    void print_info() {
        printf("\n#############################\n");
        printf("name: %s\n", this->name.c_str());
        printf("nPoints: %d\n", this->nPoints);
        printf("best_sol: %f\n", this->best_sol);
    }

    // distance_euc : computes the Euclidean distance between two points
    int distance_euc(vector<float> point_i, vector<float> point_j) {
        return round(sqrt(pow(point_i[1] - point_j[1], 2) + pow(point_i[2] - point_j[2], 2)));
    }

    // create_dist_matrix : computes the distance matrix
    vector<vector<float> > create_dist_matrix(vector<vector<float> > points, int nPoints) {
        vector<vector<float> > dist_matrix(nPoints, vector<float>(nPoints));
        for (int i = 0; i < nPoints; i++) {
            for (int j = i; j < nPoints; j++) {
                dist_matrix[i][j] = distance_euc(points[i], points[j]);
            }
        }
        vector<vector<float> > trans_dist_matrix(dist_matrix[0].size(), vector<float>(dist_matrix[0].size()));
        for (int i = 0; i < dist_matrix.size(); i++) {
            for (int j = 0; j < dist_matrix[i].size(); j++) {
                if (trans_dist_matrix[j].size() != dist_matrix.size()) {
                    trans_dist_matrix[j].resize(dist_matrix.size());
                } 
                trans_dist_matrix[j][i] = dist_matrix[i][j];
            }
        }
        vector<vector<float> > sum_of_matrices(dist_matrix[0].size(), vector<float>(dist_matrix[0].size()));
        for (int i = 0; i < dist_matrix.size(); i++) {
            for (int j = 0; j < dist_matrix[i].size(); j++) {
                sum_of_matrices[i][j] = dist_matrix[i][j] + trans_dist_matrix[i][j];
            }
        }
        return sum_of_matrices;
    }

    // string_split : tokenize a string using a delimiter
    vector<string> string_split(string input_string, string delimiter) {
        vector<string> strings_sequence;
        int begin_position = 0;
        int end_position = input_string.find(delimiter, begin_position);
        while (end_position != string::npos) {
            string string = input_string.substr(begin_position, end_position - begin_position);
            strings_sequence.push_back(string);
            begin_position = end_position + delimiter.length();
            end_position = input_string.find(delimiter, begin_position);
        }
        strings_sequence.push_back(input_string.substr(begin_position));
        return strings_sequence;
    }
};

#endif
