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
        std::size_t index;

        bool status = false;
    };

    using Strategy = Real (*) (const Data &, const Parameters &);
    using Routine = Vector (*) (const Data &);

    Data solver(const Parameters &, Routine, Strategy, Function, Gradient);
    Data solver(const Parameters &, Routine, Strategy, Function);
    Data solver(const Parameters &, Routine, Strategy);

    Vector newton_routine(const Data &);
    Vector hb_routine(const Data &);
    Vector nesterov_routine(const Data &);

    Real fixed_strategy(const Data &, const Parameters &);
    Real exponential_strategy(const Data &, const Parameters &);
    Real inverse_strategy(const Data &, const Parameters &);
    Real armijo_strategy(const Data &, const Parameters &);

    void show(const Data &);
    void show(const Data &, const Vector &);
}

#endif