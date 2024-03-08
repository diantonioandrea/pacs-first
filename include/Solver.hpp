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
        Target target; // f(x), Df(x).
        Vector point; // X_k.
        size_t step; // K-th step.
    };

    // SOLVER.

    std::pair<Vector, bool> solver(const Target &, const Parameters &, Real (*strategy) (const Data &, const Parameters &));
    
    // STRATEGIES.

    // Exponential.
    Real exponential_strategy(const Data &, const Parameters &);

    // Inverse.
    Real inverse_strategy(const Data &, const Parameters &);

    // Armijo.
    Real armijo_strategy(const Data &, const Parameters &);

}

#endif