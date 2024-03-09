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

namespace pacs {

    Arguments parse(const int &argc, char **argv) {
        Arguments arguments;

        // Looks for the arguments.verbose flag separately.
        for(size_t j = 1; j < argc; j++) {        
            std::string option = argv[j];

            if(option == "-v")
                arguments.verbose = true;
        }

        // Parses argv.
        for(size_t j = 1; j < argc; j++) {        
            std::string option = argv[j];

            if(option == "--all") {
                if(arguments.verbose)
                    std::cout << "\nUsing every routine and strategy." << std::endl;

                arguments.s_all = true;
            }

            // Routine.
            if(!arguments.s_routine) {
                if(option == "--r_newton") { // Default.
                    if(arguments.verbose)
                        std::cout << "\nUsing the Newton routine." << std::endl;

                    arguments.s_routine = true;
                }
            
                if(option == "--r_hb") {
                    if(arguments.verbose)
                        std::cout << "\nUsing the Heavy-Ball routine." << std::endl;

                    arguments.routine = pacs::hb_routine;
                    arguments.s_routine = true;
                }
                    
                
                if(option == "--r_nesterov") {
                    if(arguments.verbose)
                        std::cout << "\nUsing the Nesterov routine." << std::endl;

                    arguments.routine = pacs::hb_routine;
                    arguments.s_routine = true;
                }
            }

            // Strategy.
            if(!arguments.s_strategy) {
                if(option == "--exponential") {
                    if(arguments.verbose)
                        std::cout << "\nUsing the Exponential Decay strategy." << std::endl;

                    arguments.strategy = pacs::exponential_strategy;
                    arguments.s_strategy = true;
                }
            
                if(option == "--inverse") {
                    if(arguments.verbose)
                        std::cout << "\nUsing the Inverse Decay strategy." << std::endl;

                    arguments.strategy = pacs::inverse_strategy;
                    arguments.s_strategy = true;
                }
                    
                if(option == "--armijo") { // Default.
                    if(arguments.verbose)
                        std::cout << "\nUsing the Armijo strategy." << std::endl;

                    arguments.s_strategy = true;
                }
            }

            // Parameters file.
            if((option == "-p") && (j < argc - 1))
                arguments.filename = argv[j + 1];
        }

        return arguments;
    }

}