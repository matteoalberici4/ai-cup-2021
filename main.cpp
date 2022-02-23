// Artificial Intelligence 2021
// AI CUP 2021
// Matteo Alberici
// main.cpp

#include <vector>
#include "ProblemInstance.hpp"
#include "SolverTSP.hpp"

using namespace std;

// main
int main(int argc, char** argv ) {
    vector<string> problems;
    problems.push_back("./problems/ch130.tsp");
    problems.push_back("./problems/d198.tsp");
    problems.push_back("./problems/eil76.tsp");
    problems.push_back("./problems/fl1577.tsp");
    problems.push_back("./problems/kroA100.tsp");
    problems.push_back("./problems/lin318.tsp");
    problems.push_back("./problems/pcb442.tsp");
    problems.push_back("./problems/pr439.tsp");
    problems.push_back("./problems/rat783.tsp");
    problems.push_back("./problems/u1060.tsp");
    for (int i = 0; i < problems.size(); i++) {
        ProblemInstance * p = new ProblemInstance(problems[i]);
        p->print_info();
        SolverTSP s = SolverTSP(p);
    }
    return 0;
}