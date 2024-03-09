/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef SOLVER_PACS
#define SOLVER_PACS

#include <vector>
#include <cmath>

#include "Parameters.hpp"
#include "Vector.hpp"

namespace pacs {

    using Function = Real (*) (const Vector &);
    using Gradient = Vector (*) (const Vector &);

    /**
     * @brief Target functions and gradient structure.
     * 
     */
    struct Target {
        Function function;
        Gradient gradient;
    };

    /**
     * @brief Solver data structure.
     * 
     */
    struct Data {
        const Target target;

        Vector next;
        Vector current;
        Vector previous;

        Real size;
        size_t index;

        bool status = false;
    };

    using Strategy = Real (*) (const Data &, const Parameters &);
    using Routine = Vector (*) (const Data &);

    Data solver(const Target &, const Parameters &, Routine, Strategy);
    Data solver(const Target &, const Parameters &);

    Vector newton_routine(const Data &);
    Vector hb_routine(const Data &);
    Vector nesterov_routine(const Data &);

    Real exponential_strategy(const Data &, const Parameters &);
    Real inverse_strategy(const Data &, const Parameters &);
    Real armijo_strategy(const Data &, const Parameters &);

}

#endif