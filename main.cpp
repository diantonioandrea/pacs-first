/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

// Standard library.
#include <iostream>
#include <vector>

// Real type, vectors and parameters.
#include "include/Vector.hpp"
#include "include/Parameters.hpp"

// Default targets.
#include "include/Default.hpp"

// Solver.
#include "include/Solver.hpp"

int main(int argc, char **argv) {
    // "Splash".
    std::cout << "PACS - First Challenge." << std::endl;
    std::cout << "A gradient method for the minimization of a multivariate function." << std::endl;
    std::cout << "Andrea Di Antonio, 10655477." << std::endl;

    pacs::Target target;
    pacs::Parameters parameters = pacs::read_json("parameters.json", false);

    // Using default targets.
    target.function = pacs::target_func;
    target.gradient = pacs::target_grad;

    // Routines and strategies.
    std::vector<pacs::Routine> routines = {pacs::newton_routine, pacs::hb_routine, pacs::nesterov_routine};
    std::vector<pacs::Strategy> strategies = {pacs::exponential_strategy, pacs::inverse_strategy, pacs::armijo_strategy};

    for(auto &routine_it: routines) {
        for(auto &strategy_it: strategies) {
            pacs::Data result = pacs::solver(target, parameters, routine_it, strategy_it);
            
            std::cout << "\nPoint: " << result.next << std::endl;
            std::cout << "Convergence: " << ((result.status) ? "Yes" : "No") << std::endl;
        }
    }

    return 0;
}