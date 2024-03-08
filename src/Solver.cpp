/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#include "../include/Solver.hpp"
#include <iostream>

namespace pacs {

    // SOLVERS.

    // Newton.
    std::pair<Vector, bool> solver(const Target &target, const Parameters &parameters, Real (*strategy) (const Data &, const Parameters &)) {
        // X_k.
        Vector point = parameters.start;

        // Alpha_k.
        Real step_size = parameters.alpha;

        // Return value.
        std::pair<Vector, bool> result = {point, true};

        // Solver's data.
        Data data{target, point, 0};

        for(size_t k = 0; k < parameters.max_iter; ++k) {
            Vector gradient_point = target.target_gradient(point);
            Vector next = point - (step_size * gradient_point); // X_{k + 1}.

            // Control on the step length.
            if((next - point).norm() < parameters.step_tolerance) {
                result.first = next;
                return result;
            }

            // Control on the residual.
            if((gradient_point).norm() < parameters.residual_tolerance) {
                result.first = next;
                return result;
            }

            // X_{k + 1} -> X_k.
            point = next;

            // Updates data.
            data.step = k;
            data.point = next;

            // Evaluates the next step size with the given strategy.
            step_size = strategy(data, parameters);
        }

        // Failure.
        // Returns just the initial guess.
        result.second = false;
        return result;
    }

    // STRATEGIES.

    // Exponential.
    Real exponential_strategy(const Data &data, const Parameters &parameters) {
        return parameters.alpha * std::exp(- parameters.strategy_mu * static_cast<Real>(data.step));
    }

    // Inverse.
    Real inverse_strategy(const Data &data, const Parameters &parameters) {
        return parameters.alpha / (1.0L + parameters.strategy_mu * static_cast<Real>(data.step));
    }

    // Armijo.
    Real armijo_strategy(const Data &data, const Parameters &parameters) {
        // Target function and gradient at X_k.
        Real target_point = data.target.target_function(data.point);
        Vector gradient_point = data.target.target_gradient(data.point);

        // Alpha_k.
        Real step_size = parameters.alpha;

        // Armijo strategy.
        while(target_point - data.target.target_function(data.point - step_size * gradient_point) < parameters.strategy_sigma * step_size * std::pow(gradient_point.norm(), 2)) {
            step_size /= 2.0L;
        }

        return step_size;
    }

}