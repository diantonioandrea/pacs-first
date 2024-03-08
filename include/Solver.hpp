/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef SOLVER_PACS
#define SOLVER_PACS

#include <vector>
#include <cmath>

// Real type, parameters and vectors.
#include "Types.hpp"
#include "Parameters.hpp"
#include "Vector.hpp"

namespace pacs {

    // Solver's data.
    struct Data {
        // Functions.
        Target target; // f(x), Df(x).

        // Points.
        Vector point; // X_k.
        Vector previous; // X_{k - 1}.

        // Step data.
        size_t step; // K-th step.
    };

    // SOLVER.

    std::pair<Vector, bool> solver(const Target &, const Parameters &, Vector (*routine) (const Data &, const Real &), Real (*strategy) (const Data &, const Parameters &));

    // ROUTINES: Return X_{k + 1}.

    // Newton.
    Vector newton_routine(const Data &, const Real &);

    // Heavy-Ball.
    Vector hb_routine(const Data &, const Real &);

    // Nesterov.
    Vector nesterov_routine(const Data &, const Real &);
    
    // STRATEGIES: Return Alpha_{k + 1}.

    // Exponential.
    Real exponential_strategy(const Data &, const Parameters &);

    // Inverse.
    Real inverse_strategy(const Data &, const Parameters &);

    // Armijo.
    Real armijo_strategy(const Data &, const Parameters &);

}

#endif