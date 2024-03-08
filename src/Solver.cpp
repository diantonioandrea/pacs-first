/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#include "../include/Solver.hpp"

namespace pacs {

    // SOLVER.

    std::pair<Vector, bool> solver(const Target &target, const Parameters &parameters, Routine routine, Strategy strategy) {
        // X_0.
        Vector current = parameters.start, next = current;

        // Alpha_0.
        Real step_size = parameters.alpha;

        // Return value.
        std::pair<Vector, bool> result = {current, true};

        // Solver's data initialization.
        Data data{target, current, current, step_size, 0};

        for(size_t k = 0; k < parameters.max_iter; ++k) {
            // Evaluates the next point with the given routine.
            next = routine(data); // X_{k + 1}.

            // Control on the step length.
            if((next - current).norm() < parameters.step_tolerance) {
                result.first = next;
                return result;
            }

            // Control on the residual.
            if((target.target_gradient(next)).norm() < parameters.residual_tolerance) {
                result.first = next;
                return result;
            }

            // X_{k - 1} and X_{k}.
            data.previous = current;
            data.current = next;

            // X_{k + 1} -> X_k.
            current = next;

            // Updates data.step*.
            data.step_size = step_size;
            data.step_index = k;

            // Evaluates the next step size with the given strategy.
            step_size = strategy(data, parameters);
        }

        // Failure.
        // Returns just the initial guess.
        result.second = false;
        return result;
    }

    // Default routine (Newton) and strategy (Armijo).
    std::pair<Vector, bool> solver(const Target &target, const Parameters &parameters) {
        return solver(target, parameters, newton_routine, armijo_strategy);
    }

    // ROUTINES.

    // Newton.
    Vector newton_routine(const Data &data) {
        return data.current - (data.step_size * data.target.target_gradient(data.current));
    }

    // Heavy-Ball.
    Vector hb_routine(const Data &data) {
        Real strategy_eta = (data.step_size < 1.0L) ? 1.0L - data.step_size : 0.9L;

        return data.current - (data.step_size * data.target.target_gradient(data.current)) + strategy_eta * (data.current - data.previous);
    }

    // Nesterov.
    Vector nesterov_routine(const Data &data) {
        Real strategy_eta = (data.step_size < 1.0L) ? 1.0L - data.step_size : 0.9L;

        Vector partial = data.current + strategy_eta * (data.current - data.previous);
        return partial - data.step_size * data.target.target_gradient(data.current);
    }

    // STRATEGIES.

    // Exponential.
    Real exponential_strategy(const Data &data, const Parameters &parameters) {
        return parameters.alpha * std::exp(- parameters.strategy_mu * static_cast<Real>(data.step_index));
    }

    // Inverse.
    Real inverse_strategy(const Data &data, const Parameters &parameters) {
        return parameters.alpha / (1.0L + parameters.strategy_mu * static_cast<Real>(data.step_index));
    }

    // Armijo.
    Real armijo_strategy(const Data &data, const Parameters &parameters) {
        // Target function and gradient at X_k.
        Real target_point = data.target.target_function(data.current);
        Vector gradient_point = data.target.target_gradient(data.current);

        // Alpha_k.
        Real step_size = parameters.alpha;

        // Armijo strategy.
        while(target_point - data.target.target_function(data.current - step_size * gradient_point) < parameters.strategy_sigma * step_size * std::pow(gradient_point.norm(), 2)) {
            step_size /= 2.0L;
        }

        return step_size;
    }

}