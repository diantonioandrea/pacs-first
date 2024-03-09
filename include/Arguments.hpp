/**
 * @file Arguments.hpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ARGUMENTS_PACS
#define ARGUMENTS_PACS

#include <iostream>
#include <string>

#include "../include/Solver.hpp"

namespace pacs {

    /**
     * @brief Arguments structure.
     * 
     */
    struct Arguments {
        bool verbose = false;
        bool s_strategy = false;
        bool s_routine = false;
        bool s_all = false;
        Routine routine = newton_routine;
        Strategy strategy = armijo_strategy;
        std::string filename = "parameters.json";
    };

    Arguments parse(const int &, char **);
}

#endif