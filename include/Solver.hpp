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

    // Data.
    struct Solver_Data {
        Target target; // f(x), Df(x).
        Vector point; // X_k.
        size_t step; // K.
    };

    // SOLVERS.

    // Newton.
    std::pair<Vector, bool> newton_solver(const Target &, const Parameters &, Real (*strategy) (const Solver_Data &, const Parameters &));
    
    // STRATEGIES.

    // Exponential.
    Real exponential_strategy(const Solver_Data &, const Parameters &);

    // Inverse.
    Real inverse_strategy(const Solver_Data &, const Parameters &);

    // Armijo.
    Real armijo_strategy(const Solver_Data &, const Parameters &);

}

#endif