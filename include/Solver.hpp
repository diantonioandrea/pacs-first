/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef SOLVER_PACS
#define SOLVER_PACS

#include <vector>
#include <cmath>

// Real type, parameters and vectors.
#include "Type.hpp"
#include "Parameters.hpp"
#include "Vector.hpp"

namespace pacs {

    // Target aliases.
    using Target_Function = Real (*) (const Vector &);
    using Target_Gradient = Vector (*) (const Vector &);

    // Target function and its gradient.
    struct Target {
        Target_Function target_function;
        Target_Gradient target_gradient;
    };

    // Solver's data.
    // Data that changes during the solver's main cycle.
    struct Data {
        // Functions.
        const Target target;

        // Points.
        Vector current; // X_k.
        Vector previous; // X_{k - 1}.

        // Step data.
        Real step_size; // K-th step size.
        size_t step_index; // K-th step index (K).
    };

    // Solver aliases.
    using Strategy = Real (*) (const Data &, const Parameters &);
    using Routine = Vector (*) (const Data &);

    // SOLVER.

    std::pair<Vector, bool> solver(const Target &, const Parameters &, Routine routine, Strategy strategy);
    std::pair<Vector, bool> solver(const Target &, const Parameters &); // Default routine and strategy.

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