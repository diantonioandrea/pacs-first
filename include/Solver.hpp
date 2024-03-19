/**
 * @file Solver.hpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SOLVER_PACS
#define SOLVER_PACS

#include <Vector.hpp>
#include <Target.hpp>
#include <Parameters.hpp>

namespace pacs {

    /**
     * @brief Solver data structure.
     * 
     */
    struct Data {
        Target target;

        Vector next;
        Vector current;
        Vector previous;

        Real size;
        size_t index;

        bool status = false;
    };

    using Strategy = Real (*) (Data &, const Parameters &);
    using Routine = Vector (*) (Data &);

    Data solver(const Parameters &, Routine, Strategy, Function, Gradient);
    Data solver(const Parameters &, Routine, Strategy, Function);
    Data solver(const Parameters &, Routine, Strategy);

    Vector newton_routine(Data &);
    Vector hb_routine(Data &);
    Vector nesterov_routine(Data &);

    Real fixed_strategy(Data &, const Parameters &);
    Real exponential_strategy(Data &, const Parameters &);
    Real inverse_strategy(Data &, const Parameters &);
    Real armijo_strategy(Data &, const Parameters &);

    void show(Data &);
    void show(Data &, const Vector &);
}

#endif