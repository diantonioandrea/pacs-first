/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef ARGUMENTS_PACS
#define ARGUMENTS_PACS

#include <iostream>

// Filename.
#include <string>

// Routines and strategies
#include "../include/Solver.hpp"

namespace pacs {

    // Arguments struct.
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