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

#include <Solver.hpp>

namespace pacs {

    /**
     * @brief Arguments structure.
     * 
     */
    struct Arguments {
        bool verbose = false;
        bool help = false;

        bool numerical = false;
        bool s_strategy = false;
        bool s_routine = false;
        bool s_all = false;
        
        Routine routine = newton_routine;
        Strategy strategy = fixed_strategy;
        
        std::string filename = "parameters.json";
    };

    void challenge_splash(char **);
    Arguments parse(const int &, char **);
}

#endif