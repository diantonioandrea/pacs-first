/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef PARAMETERS_PACS
#define PARAMETERS_PACS

// Real type and vectors.
#include "Type.hpp"
#include "Vector.hpp"

namespace pacs {

    // Default parameters.
    struct Parameters {
        // X_0.
        Vector start = Vector(2, {0.0L, 0.0L});

        // Alpha_0.
        Real alpha = 1.0E-1L;

        // Tolerances.
        Real step_tolerance = 1.0E-6L;
        Real residual_tolerance = 1.0E-6L;
        
        // Maximum number of iterations.
        size_t max_iterations = 10000;

        // Strategy parameters.
        Real strategy_mu = 0.2L; // Decays.
        Real strategy_sigma = 0.25L; // Armijo.
    };
    
}

#endif