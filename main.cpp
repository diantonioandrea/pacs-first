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

// Default targets.
#include "include/Default.hpp"

// Solver.
#include "include/Solver.hpp"

// Parser.
#include "include/Arguments.hpp"

// Results printer.
void print_results(const pacs::Data &);


int main(int argc, char **argv) {
    // "Help".
    if(argc <= 1) {
        std::cout << "Usage: ./main  [-v]  [-p FILENAME]  [--all]  [--r_(ROUTINE)]  [--(STRATEGY)]" << std::endl;
        std::cout << "\nExamples:" << std::endl;
        std::cout << "\t./main -v --all" << std::endl;
        std::cout << "\t./main --r_nesterov --armijo" << std::endl;
        return 0;
    }

    // "Splash".
    std::cout << "PACS - First Challenge." << std::endl;
    std::cout << "A gradient method for the minimization of a multivariate function." << std::endl;
    std::cout << "Andrea Di Antonio, 10655477." << std::endl;

    // Loads every routine and strategy.
    std::vector<pacs::Routine> routines = {pacs::newton_routine, pacs::hb_routine, pacs::nesterov_routine};
    std::vector<pacs::Strategy> strategies = {pacs::exponential_strategy, pacs::inverse_strategy, pacs::armijo_strategy};

    // Arguments and parameters.
    pacs::Arguments args = pacs::parse(argc, argv);
    pacs::Parameters parameters = pacs::read_json(args.filename, args.verbose);

    // Default targets.
    pacs::Target target{pacs::target_func, pacs::target_grad};

    // Execution.
    if(args.s_all) {

        // Runs every strategy and routine (--all).
        for(auto &routine_it: routines) {
            for(auto &strategy_it: strategies)
                print_results(pacs::solver(target, parameters, routine_it, strategy_it));
        }

    } else if(args.s_routine || args.s_strategy) {

        if(!args.s_strategy) {
            if(args.verbose)
                    std::cout << "Using every strategy." << std::endl;

            // Runs the specified routine on every strategy.
            for(auto &strategy_it: strategies)
                print_results(pacs::solver(target, parameters, args.routine, strategy_it));

        } else if(!args.s_routine) {

            if(args.verbose)
                    std::cout << "Using every routine." << std::endl;

            // Runs the specified strategy with every routine.
            for(auto &routine_it: routines)
                print_results(pacs::solver(target, parameters, routine_it, args.strategy));

        } else

            // Runs only the specified routine and strategy.
            print_results(pacs::solver(target, parameters, args.routine, args.strategy));

    } else { // Arguments error.
        std::cerr << "\nCheck your arguments!" << std::endl;
        return -1;
    }

    return 0;
}


// Prints the result of a single run.
void print_results(const pacs::Data &result) {
    std::cout << "\nMinimum: " << result.next << std::endl;
    std::cout << "Convergence: " << ((result.status) ? "Yes" : "No") << std::endl;
}