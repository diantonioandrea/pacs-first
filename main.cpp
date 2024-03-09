/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
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

int main(int argc, char **argv) {
    // "Help".
    if(argc <= 1) {
        std::cout << "Usage: ./main  [-v]  [--all]  [--r_(ROUTINE)]  [--(STRATEGY)]" << std::endl;
        std::cout << "\nExamples:" << std::endl;
        std::cout << "\t./main -v --all" << std::endl;
        std::cout << "\t./main --r_newton --armijo" << std::endl;
        return 0;
    }

    // "Splash".
    std::cout << "PACS - First Challenge." << std::endl;
    std::cout << "A gradient method for the minimization of a multivariate function." << std::endl;
    std::cout << "Andrea Di Antonio, 10655477." << std::endl;

    // Loads every routine and strategy.
    std::vector<pacs::Routine> routines = {pacs::newton_routine, pacs::hb_routine, pacs::nesterov_routine};
    std::vector<pacs::Strategy> strategies = {pacs::exponential_strategy, pacs::inverse_strategy, pacs::armijo_strategy};

    // Default routine and strategy.
    pacs::Routine routine = pacs::newton_routine;
    pacs::Strategy strategy = pacs::armijo_strategy;

    // Default filename.
    std::string filename = "parameters.json";

    // Options.
    bool s_routine = false, s_strategy = false, s_all = false;
    bool verbose = false;

    // Looks for the verbose flag separately.
    for(size_t j = 1; j < argc; j++) {        
        std::string option = argv[j];

        if(option == "-v")
            verbose = true;
    }

    // Parses argv.
    for(size_t j = 1; j < argc; j++) {        
        std::string option = argv[j];

        if(option == "--all") {
            if(verbose)
                std::cout << "\nUsing every routine and strategy." << std::endl;

            s_all = true;
        }

        // Routine.
        if(!s_routine) {
            if(option == "--r_newton") { // Default.
                if(verbose)
                    std::cout << "\nUsing the Newton routine." << std::endl;

                s_routine = true;
            }
        
            if(option == "--r_hb") {
                if(verbose)
                    std::cout << "\nUsing the Heavy-Ball routine." << std::endl;

                routine = pacs::hb_routine;
                s_routine = true;
            }
                
            
            if(option == "--r_nesterov") {
                if(verbose)
                    std::cout << "\nUsing the Nesterov routine." << std::endl;

                routine = pacs::hb_routine;
                s_routine = true;
            }
        }

        // Strategy.
        if(!s_strategy) {
            if(option == "--exponential") {
                if(verbose)
                    std::cout << "\nUsing the Exponential Decay strategy." << std::endl;

                strategy = pacs::exponential_strategy;
                s_strategy = true;
            }
        
            if(option == "--inverse") {
                if(verbose)
                    std::cout << "\nUsing the Inverse Decay strategy." << std::endl;

                strategy = pacs::inverse_strategy;
                s_strategy = true;
            }
                
            if(option == "--armijo") { // Default.
                if(verbose)
                    std::cout << "\nUsing the Armijo strategy." << std::endl;

                s_strategy = true;
            }
        }
    }

    // Target and parameters.
    pacs::Target target;
    pacs::Parameters parameters = pacs::read_json(filename, verbose);

    // Using default targets.
    target.function = pacs::target_func;
    target.gradient = pacs::target_grad;

    // Execution.
    if(s_all) { // "--all" case.
        for(auto &routine_it: routines) {
            for(auto &strategy_it: strategies) {
                pacs::Data result = pacs::solver(target, parameters, routine_it, strategy_it);
                
                std::cout << "\nMinimum: " << result.next << std::endl;
                std::cout << "Convergence: " << ((result.status) ? "Yes" : "No") << std::endl;
            }
        }
    } else if(s_routine || s_strategy) {
        if(!s_strategy) { // Runs the specified routine on every strategy.
            if(verbose)
                    std::cout << "Using every strategy." << std::endl;

            for(auto &strategy_it: strategies) {
                pacs::Data result = pacs::solver(target, parameters, routine, strategy_it);
                
                std::cout << "\nMinimum: " << result.next << std::endl;
                std::cout << "Convergence: " << ((result.status) ? "Yes" : "No") << std::endl;
            }
        } else if(!s_routine) { // Runs the specified strategy with every routine.
            if(verbose)
                    std::cout << "Using every routine." << std::endl;

            for(auto &routine_it: routines) {
                pacs::Data result = pacs::solver(target, parameters, routine_it, strategy);
                
                std::cout << "\nMinimum: " << result.next << std::endl;
                std::cout << "Convergence: " << ((result.status) ? "Yes" : "No") << std::endl;
            }
        } else { // Runs only the specified routine and strategy.
            pacs::Data result = pacs::solver(target, parameters, routine, strategy);
                    
            std::cout << "\nMinimum: " << result.next << std::endl;
            std::cout << "Convergence: " << ((result.status) ? "Yes" : "No") << std::endl;
        }
    } else {
        std::cerr << "\nCheck your arguments!" << std::endl;
        return -1;
    }

    return 0;
}