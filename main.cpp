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

// Default function.
pacs::Real target_func(const pacs::Vector &x);
pacs::Vector target_grad(const pacs::Vector &x);


int main(int argc, char **argv) {
    pacs::Target target;
    pacs::Parameters parameters;

    // Using default targets.
    target.target_function = target_func;
    target.target_gradient = target_grad;

    // Routines and strategies.
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


// Default functions definition.
pacs::Real target_func(const pacs::Vector &x) {
    #ifndef NDEBUG
    assert(x.length() == 2);
    #endif

    return x[0] * x[1] + 4 * std::pow(x[0], 4) + std::pow(x[1], 2) + 3 * x[0];
}

pacs::Vector target_grad(const pacs::Vector &x) {
    #ifndef NDEBUG
    assert(x.length() == 2);
    #endif

    pacs::Vector gradient = pacs::Vector(2);

    gradient[0] = x[1] + 16.0L * std::pow(x[0], 3) + 3.0L;
    gradient[1] = x[0] + 2.0L * x[1];

    return gradient;
}