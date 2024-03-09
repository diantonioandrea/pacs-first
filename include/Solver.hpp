/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef SOLVER_PACS
#define SOLVER_PACS

#include <vector>
#include <cmath>

// Real type, parameters and vectors.
#include "Parameters.hpp"
#include "Vector.hpp"

namespace pacs {

    // Target aliases.
    using Function = Real (*) (const Vector &);
    using Gradient = Vector (*) (const Vector &);

    // Target struct.
    struct Target {
        Function function;
        Gradient gradient;
    };

    // Solver's data struct.
    // Data that changes during the solver's main cycle.
    struct Data {
        // Functions.
        const Target target;

        // Points.
        Vector next; // X_k.
        Vector current; // X_k.
        Vector previous; // X_{k - 1}.

        // Step data.
        Real size; // K-th step size.
        size_t index; // K-th step index (K).

        // Output.
        bool status = false;
    };

    // Solver aliases.
    using Strategy = Real (*) (const Data &, const Parameters &);
    using Routine = Vector (*) (const Data &);

    // SOLVER.

    Data solver(const Target &, const Parameters &, Routine, Strategy);
    Data solver(const Target &, const Parameters &); // Default routine (Newton) and strategy (Armijo).

    // ROUTINES: Return X_{k + 1}.

    Vector newton_routine(const Data &); // Newton.
    Vector hb_routine(const Data &); // Heavy-Ball.
    Vector nesterov_routine(const Data &); // Nesterov.
    
    // STRATEGIES: Return Alpha_{k + 1}.

    Real exponential_strategy(const Data &, const Parameters &); // Exponential.
    Real inverse_strategy(const Data &, const Parameters &); // Inverse.
    Real armijo_strategy(const Data &, const Parameters &); // Armijo.

}

#endif