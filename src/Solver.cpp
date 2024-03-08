/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#include "../include/Solver.hpp"
#include <iostream>

namespace pacs {

    // SOLVERS.

    // Newton.
    std::pair<Vector, bool> solver(const Target &target, const Parameters &parameters, Vector (*routine) (const Data &, const Real &), Real (*strategy) (const Data &, const Parameters &)) {
        // X_k.
        Vector point = parameters.start, next = parameters.start;

        // Alpha_k.
        Real step_size = parameters.alpha;

        // Return value.
        std::pair<Vector, bool> result = {point, true};

        // Solver's data.
        Data data{target, point, point, 0};

        for(size_t k = 0; k < parameters.max_iter; ++k) {
            // Evaluates the next point with the given routine.
            next = routine(data, step_size); // X_{k + 1}.

            // Control on the step length.
            if((next - point).norm() < parameters.step_tolerance) {
                result.first = next;
                return result;
            }

            // Control on the residual.
            if((target.target_gradient(next)).norm() < parameters.residual_tolerance) {
                result.first = next;
                return result;
            }

            // X_{k - 1}.
            data.previous = point;

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

    // ROUTINES.

    // Newton.
    Vector newton_routine(const Data &data, const Real &step_size) {
        return data.point - (step_size * data.target.target_gradient(data.point));
    }

    // Heavy-Ball.
    Vector hb_routine(const Data &data, const Real &step_size) {
        Real strategy_eta = (step_size < 1.0L) ? 1.0L - step_size : 0.9L;

        return data.point - (step_size * data.target.target_gradient(data.point)) + strategy_eta * (data.point - data.previous);
    }

    // Nesterov.
    Vector nesterov_routine(const Data &data, const Real &step_size) {
        Real strategy_eta = (step_size < 1.0L) ? 1.0L - step_size : 0.9L;

        Vector partial = data.point + strategy_eta * (data.point - data.previous);
        return partial - step_size * data.target.target_gradient(data.point);
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