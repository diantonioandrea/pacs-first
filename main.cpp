/**
 * @file main.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>

// Includes.
#include "main.hpp"

int main(int argc, char **argv) {
    // Default "splash".
    std::cout << "PACS - First challenge - Andrea Di Antonio." << std::endl;

    // Arguments.
    pacs::Arguments args = pacs::parse(argc, argv);

    // Help.
    if(args.help) {
        pacs::challenge_splash(argv);
        return 0;
    }

    // Parameters.
    pacs::Parameters parameters = pacs::read_json(args.filename, args.verbose);

    // Single run with the specified routine and strategy.
    if(args.muparser) { // Uses MuParser to define the target function.
        pacs::show(pacs::solver(parameters, args.routine, args.strategy));
    } else if(args.numerical) { // Default target function (numerical gradient).
        pacs::show(pacs::solver(parameters, args.routine, args.strategy, pacs::target_func));
    } else { // Default target function and gradient.
        pacs::show(pacs::solver(parameters, args.routine, args.strategy, pacs::target_func, pacs::target_grad));
    }

    return 0;
}