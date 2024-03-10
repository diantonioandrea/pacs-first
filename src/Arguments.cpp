/**
 * @file Arguments.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Arguments.hpp"

#include <cassert>

namespace pacs {

    /**
     * @brief Prints a "splash" on missing arguments.
     * 
     */
    void challenge_splash(char **argv) {
        std::cout << "Usage: " << argv[0] << "  [-h/--help]  [-v]  [-n]  [-p (FILENAME)]  [--all]  [--r_(ROUTINE)]  [--(STRATEGY)]" << std::endl;
        std::cout << "\nExamples:" << std::endl;
        std::cout << "\t./main -v --all" << std::endl;
        std::cout << "\t./main --r_nesterov --armijo" << std::endl;
    }

    /**
     * @brief Parses argv looking for arguments needed by this program.
     * 
     * @param argc 
     * @param argv 
     * @return Arguments 
     */
    Arguments parse(const int &argc, char **argv) {
        Arguments arguments;

        // Looks for the arguments.verbose and arguments.help flag separately.
        for(size_t j = 1; j < argc; j++) {        
            std::string option = argv[j];

            if(option == "-v")
                arguments.verbose = true;

            if((option == "-h") || (option == "--help")) {
                arguments.help = true;
                return arguments;
            }
        }

        // Parses argv.
        for(size_t j = 1; j < argc; j++) {        
            std::string option = argv[j];

            if(option == "--all") {
                if(arguments.verbose)
                    std::cout << "Using every routine and strategy." << std::endl;

                arguments.s_all = true;
            }

            // Numerical solution.
            if(option == "-n") {
                if(arguments.verbose)
                    std::cout << "Considering numerical gradient." << std::endl;

                arguments.numerical = true;
            }

            // Routine.
            if(!arguments.s_routine) {
                if(option == "--r_newton") {
                    if(arguments.verbose)
                        std::cout << "Using the Newton routine." << std::endl;

                    arguments.s_routine = true;
                }
            
                if(option == "--r_hb") {
                    if(arguments.verbose)
                        std::cout << "Using the Heavy-Ball routine." << std::endl;

                    arguments.routine = hb_routine;
                    arguments.s_routine = true;
                }
                    
                
                if(option == "--r_nesterov") {
                    if(arguments.verbose)
                        std::cout << "Using the Nesterov routine." << std::endl;

                    arguments.routine = hb_routine;
                    arguments.s_routine = true;
                }
            }

            // Strategy.
            if(!arguments.s_strategy) {
                if(option == "--fixed") {
                    if(arguments.verbose)
                        std::cout << "Using the Fixed strategy." << std::endl;

                    arguments.s_strategy = true;
                }

                if(option == "--exponential") {
                    if(arguments.verbose)
                        std::cout << "Using the Exponential Decay strategy." << std::endl;

                    arguments.strategy = exponential_strategy;
                    arguments.s_strategy = true;
                }
            
                if(option == "--inverse") {
                    if(arguments.verbose)
                        std::cout << "Using the Inverse Decay strategy." << std::endl;

                    arguments.strategy = inverse_strategy;
                    arguments.s_strategy = true;
                }
                    
                if(option == "--armijo") {
                    if(arguments.verbose)
                        std::cout << "Using the Armijo strategy." << std::endl;

                    arguments.strategy = armijo_strategy;
                    arguments.s_strategy = true;
                }
            }

            // Parameters file.
            if((option == "-p") && (j < argc - 1))
                arguments.filename = argv[j + 1];
        }

        // Checks.
        if((arguments.routine == nesterov_routine) || (arguments.routine == hb_routine)) {
            assert(arguments.strategy == fixed_strategy);
        }

        return arguments;
    }

}