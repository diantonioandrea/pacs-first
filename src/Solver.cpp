/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#include "../include/Solver.hpp"

namespace pacs {

    /**
     * @brief Solver function for the minimum problem.
     * 
     * @param target Target struct containing the target function and gradient.
     * @param params Parameters struct containing the solver parameters.
     * @param routine Solver routine for the next X value.
     * @param strategy Solver strategy for the next Alpha value.
     * @return Data 
     */
    Data solver(const Target &target, const Parameters &params, Routine routine, Strategy strategy) {
        #ifndef NDEBUG
        assert(params.alpha > 0.0L);

        assert(params.step_tolerance > 0.0L);
        assert(params.residual_tolerance > 0.0L);

        assert(params.max_iterations > 0);

        assert(params.strategy_mu > 0);
        assert(params.strategy_sigma > 0);
        assert(params.strategy_sigma < 0.5);
        #endif

        // Solver's data initialization.
        Data data{target, params.start, params.start, params.start, params.alpha, 0};

        // Controls and tolerances.
        Real step_con = 0.0L, res_con = 0.0L;
        Real step_tol = params.step_tolerance, res_tol = params.residual_tolerance;
        size_t max_it = params.max_iterations;

        do {
            // Evaluates the next point with the given routine.
            data.next = routine(data); // X_{k + 1}.

            // Control values.
            step_con = (data.next - data.current).norm();
            res_con = target.gradient(data.next).norm();

            // X_{k - 1} and X_{k}.
            data.previous = data.current; // Needed for Heavy-Ball and Nesterov.
            data.current = data.next;

            // Updates data.size and data.index.
            data.index++;
            data.size = strategy(data, params); // Evaluates the next step size with the given strategy.
            
        } while((data.index < max_it) && (step_con >= step_tol) && (res_con >= res_tol));

        // Achieved convergence.
        if(data.index < max_it)
            data.status = true;
        
        return data;
    }

    /**
     * @brief Default solver routine (Newton) and strategy (Armijo).
     * 
     * @param target 
     * @param params 
     * @return Data 
     */
    Data solver(const Target &target, const Parameters &params) {
        return solver(target, params, newton_routine, armijo_strategy);
    }

    /**
     * @brief Newton routine.
     * 
     * @param data 
     * @return Vector 
     */
    Vector newton_routine(const Data &data) {
        return data.current - (data.size * data.target.gradient(data.current));
    }

    /**
     * @brief Heavy-Ball routine.
     * 
     * @param data 
     * @return Vector 
     */
    Vector hb_routine(const Data &data) {
        Real strategy_eta = (data.size < 1.0L) ? 1.0L - data.size : 0.9L;

        return data.current - (data.size * data.target.gradient(data.current)) + strategy_eta * (data.current - data.previous);
    }

    /**
     * @brief Nesterov routine.
     * 
     * @param data 
     * @return Vector 
     */
    Vector nesterov_routine(const Data &data) {
        Real strategy_eta = (data.size < 1.0L) ? 1.0L - data.size : 0.9L;

        Vector partial = data.current + strategy_eta * (data.current - data.previous);
        return partial - data.size * data.target.gradient(data.current);
    }

    /**
     * @brief Exponential decay strategy.
     * 
     * @param data 
     * @param params 
     * @return Real 
     */
    Real exponential_strategy(const Data &data, const Parameters &params) {
        return params.alpha * std::exp(- params.strategy_mu * static_cast<Real>(data.index));
    }

    /**
     * @brief Inverse decay strategy.
     * 
     * @param data 
     * @param params 
     * @return Real 
     */
    Real inverse_strategy(const Data &data, const Parameters &params) {
        return params.alpha / (1.0L + params.strategy_mu * static_cast<Real>(data.index));
    }

    /**
     * @brief Armijo strategy.
     * 
     * @param data 
     * @param params 
     * @return Real 
     */
    Real armijo_strategy(const Data &data, const Parameters &params) {
        // Target function and gradient at X_k.
        Real target_point = data.target.function(data.current);
        Vector gradient_point = data.target.gradient(data.current);
        Real gradient_point_norm = std::pow(gradient_point.norm(), 2);

        // Alpha_k.
        Real step_size = params.alpha;

        // Armijo strategy.
        while(target_point - data.target.function(data.current - step_size * gradient_point) < params.strategy_sigma * step_size * gradient_point_norm) {
            step_size /= 2.0L;
        }

        return step_size;
    }

}