/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

// Standard library.
#include <iostream>
#include <vector>

// Real type, vectors and default parameters.
#include "include/Type.hpp"
#include "include/Vector.hpp"
#include "include/Parameters.hpp"

// Solver.
#include "include/Solver.hpp"

int main(int argc, char **argv) {
    pacs::Target target;
    pacs::Parameters parameters;

    std::vector<pacs::Routine> routines = {pacs::newton_routine, pacs::hb_routine, pacs::nesterov_routine};
    std::vector<pacs::Strategy> strategies = {pacs::exponential_strategy, pacs::inverse_strategy, pacs::armijo_strategy};

    for(auto &routine_it: routines) {
        for(auto &strategy_it: strategies) {
            std::pair<pacs::Vector, bool> result = pacs::solver(target, parameters, routine_it, strategy_it);
            std::cout << "Point: " << result.first << std::endl;
            std::cout << "Convergence: " << ((result.second) ? "Yes" : "No") << std::endl << std::endl;
        }
    }

    return 0;
}