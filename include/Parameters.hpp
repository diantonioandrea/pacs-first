/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef PARAMETERS_PACS
#define PARAMETERS_PACS

// Real type and vectors.
#include "Types.hpp"
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
        size_t max_iter = 10000;

        // Strategy parameters.
        Real strategy_mu = 0.2L; // Decays.
        Real strategy_sigma = 0.25L; // Armijo.
    };

    // Default target function and its gradient.
    struct Target {
        Real target_function(const Vector &x) const {
            assert(x.length() == 2);

            return x[0] * x[1] + 4 * std::pow(x[0], 4) + std::pow(x[1], 2) + 3 * x[0];
        }

        Vector target_gradient(const Vector &x) const {
            assert(x.length() == 2);

            Vector gradient = Vector(2);

            gradient[0] = x[1] + 16.0L * std::pow(x[0], 3) + 3.0L;
            gradient[1] = x[0] + 2.0L * x[1];

            return gradient;
        }
    };
    
}

#endif