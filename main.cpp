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
using namespace pacs; // Readability.

int main(int argc, char **argv) {
    // Default "splash".
    std::cout << "PACS - First challenge." << std::endl;

    // Arguments.
    Arguments args = parse(argc, argv);

    // Help.
    if(args.help) {
        challenge_splash(argv);
        return 0;
    }

    // Parameters.
    Parameters parameters = read_json(args.filename, args.verbose);

    // Default targets.
    // Checks for numerical option.
    Target target = (args.numerical) ? Target{target_func} : Target{target_func, target_grad};

    // Single run with the specified routine and strategy.
    // Default: Newton + Fixed.
    show(solver(target, parameters, args.routine, args.strategy));
    return 0;
}