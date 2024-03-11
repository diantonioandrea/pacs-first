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
    std::cout << "PACS - First challenge." << std::endl;

    // Arguments.
    pacs::Arguments args = pacs::parse(argc, argv);

    // Help.
    if(args.help) {
        pacs::challenge_splash(argv);
        return 0;
    }

    // Parameters.
    pacs::Parameters parameters = pacs::read_json(args.filename, args.verbose);

    // Default targets.
    // Checks for numerical option.
    pacs::Target target = (args.numerical) ? pacs::Target{pacs::target_func} : pacs::Target{pacs::target_func, pacs::target_grad};

    // Single run with the specified routine and strategy.
    // Default: Newton + Fixed.
    pacs::show(pacs::solver(target, parameters, args.routine, args.strategy));
    return 0;
}