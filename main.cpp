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