/**
 * @file main.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// Standard library.
#include <iostream>
#include <vector>
#include <string>

// Real type, vectors and parameters.
#include "include/Vector.hpp"
#include "include/Parameters.hpp"

// Target structure.
#include "include/Target.hpp"

// Default targets.
#include "include/Default.hpp"

// Solver.
#include "include/Solver.hpp"

// Parser.
#include "include/Arguments.hpp"

// For readability.
// I wouldn't use it in a bigger project.
using namespace pacs;

int main(int argc, char **argv) {
    // "Splash" on empty ./main.
    if(argc <= 1) {
        splash(argv);
        return 0;
    }

    // Loads every routine and strategy.
    std::vector<Routine> routines = {newton_routine, hb_routine, nesterov_routine};
    std::vector<Strategy> strategies = {exponential_strategy, inverse_strategy, armijo_strategy};

    // Arguments and parameters.
    Arguments args = parse(argc, argv);
    Parameters parameters = read_json(args.filename, args.verbose);

    // Default targets.
    Target target{target_func, target_grad};

    // Execution.
    if(args.s_all) {

        // Runs every strategy and routine (--all).
        for(auto &routine_it: routines) {
            for(auto &strategy_it: strategies)
                show(solver(target, parameters, routine_it, strategy_it));
        }

    } else if(args.s_routine || args.s_strategy) {

        if(!args.s_strategy) {
            if(args.verbose)
                    std::cout << "\nUsing every strategy." << std::endl;

            // Runs the specified routine on every strategy.
            for(auto &strategy_it: strategies)
                show(solver(target, parameters, args.routine, strategy_it));

        } else if(!args.s_routine) {

            if(args.verbose)
                    std::cout << "\nUsing every routine." << std::endl;

            // Runs the specified strategy with every routine.
            for(auto &routine_it: routines)
                show(solver(target, parameters, routine_it, args.strategy));

        } else

            // Runs only the specified routine and strategy.
            show(solver(target, parameters, args.routine, args.strategy));

    } else { // Arguments error.
        std::cerr << "\nCheck your arguments!" << std::endl;
        return -1;
    }

    return 0;
}