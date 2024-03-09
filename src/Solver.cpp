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

        assert(parameters.max_iterations > 0);

        assert(parameters.strategy_mu > 0);
        assert(parameters.strategy_sigma > 0);
        assert(parameters.strategy_sigma < 0.5);
        #endif

        // Return value.
        std::pair<Vector, bool> result = {parameters.start, false};

        // Solver's data initialization.
        Data data{target, parameters.start, parameters.start, parameters.start, parameters.alpha, 0};

        // Controls and tolerances.
        Real step_con = 0.0L, res_con = 0.0L;
        Real step_tol = parameters.step_tolerance, res_tol = parameters.residual_tolerance;
        size_t max_it = parameters.max_iterations;

        do {
            // Evaluates the next point with the given routine.
            data.next = routine(data); // X_{k + 1}.

            // Control values.
            step_con = (data.next - data.current).norm();
            res_con = target.gradient(data.next).norm();

            // X_{k - 1} and X_{k}.
            data.previous = data.current;
            data.current = data.next;

            // X_{k + 1} -> X_k.
            data.current = data.next;

            // Updates data.size and data.index.
            data.index++; // Also updates step.

            // Evaluates the next step size with the given strategy.
            data.size = strategy(data, parameters);
        } while((data.index < max_it) && (step_con >= step_tol) && (res_con >= res_tol));

        if(data.index < max_it) { // Achieved convergence.
            result.first = data.next;
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
        return data.current - (data.size * data.target.gradient(data.current));
    }

    // Heavy-Ball.
    Vector hb_routine(const Data &data) {
        Real strategy_eta = (data.size < 1.0L) ? 1.0L - data.size : 0.9L;

        return data.current - (data.size * data.target.gradient(data.current)) + strategy_eta * (data.current - data.previous);
    }

    // Nesterov.
    Vector nesterov_routine(const Data &data) {
        Real strategy_eta = (data.size < 1.0L) ? 1.0L - data.size : 0.9L;

        Vector partial = data.current + strategy_eta * (data.current - data.previous);
        return partial - data.size * data.target.gradient(data.current);
    }

    // STRATEGIES.

    // Exponential.
    Real exponential_strategy(const Data &data, const Parameters &parameters) {
        return parameters.alpha * std::exp(- parameters.strategy_mu * static_cast<Real>(data.index));
    }

    // Inverse.
    Real inverse_strategy(const Data &data, const Parameters &parameters) {
        return parameters.alpha / (1.0L + parameters.strategy_mu * static_cast<Real>(data.index));
    }

    // Armijo.
    Real armijo_strategy(const Data &data, const Parameters &parameters) {
        // Target function and gradient at X_k.
        Real target_point = data.target.function(data.current);
        Vector gradient_point = data.target.gradient(data.current);

        // Alpha_k.
        Real step_size = parameters.alpha;

        // Armijo strategy.
        while(target_point - data.target.function(data.current - step_size * gradient_point) < parameters.strategy_sigma * step_size * std::pow(gradient_point.norm(), 2)) {
            step_size /= 2.0L;
        }

        return step_size;
    }

}