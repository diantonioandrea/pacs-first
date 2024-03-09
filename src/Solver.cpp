/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#include "../include/Solver.hpp"

namespace pacs {

    // SOLVER.

    std::pair<Vector, bool> solver(const Target &target, const Parameters &parameters, Routine routine, Strategy strategy) {
        #ifndef NDEBUG
        assert(parameters.alpha > 0.0L);

        assert(parameters.step_tolerance > 0.0L);
        assert(parameters.residual_tolerance > 0.0L);

        assert(parameters.max_iter > 0);

        assert(parameters.strategy_mu > 0);
        assert(parameters.strategy_sigma > 0);
        assert(parameters.strategy_sigma < 0.5);
        #endif
        
        // X_0.
        Vector current = parameters.start, next = current;

        // Alpha_0.
        Real step_size = parameters.alpha;

        // Return value.
        std::pair<Vector, bool> result = {parameters.start, false};

        // Solver's data initialization.
        Data data{target, current, current, step_size, 0};

        // Step index.
        size_t step = 0;

        // Controls.
        Real step_control = 0.0L;
        Real residual_control = 0.0L;

        do {
            // Evaluates the next point with the given routine.
            next = routine(data); // X_{k + 1}.

            // Control values.
            step_control = (next - current).norm();
            residual_control = target.target_gradient(next).norm();

            // X_{k - 1} and X_{k}.
            data.previous = current;
            data.current = next;

            // X_{k + 1} -> X_k.
            current = next;

            // Updates data.step_size and data.step_index.
            data.step_size = step_size;
            data.step_index = step;

            // Evaluates the next step size with the given strategy.
            step_size = strategy(data, parameters);

            ++step;
        } while((step < parameters.max_iter) && \
            (step_control >= parameters.step_tolerance) && \
            (residual_control >= parameters.residual_tolerance));

        // Achieved convergence.
        if(step < parameters.max_iter) {
            result.first = next;
            result.second = true;
        }
        
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