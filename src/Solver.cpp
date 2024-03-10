/**
 * @file Solver.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Solver.hpp"

#include <cmath>

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
        // Solver's data initialization.
        Data data{target, params.guess, params.guess, params.guess, params.alpha, 0};

        // Controls and tolerances.
        Real step_con = 0.0L, res_con = 0.0L;

        // Short names.
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
            data.size = strategy(data, params); // Evaluates the next Alpha with the given strategy.
            
        } while((data.index < max_it) && (step_con >= step_tol) && (res_con >= res_tol));

        // Achieved convergence.
        if(data.index < max_it)
            data.status = true;
        
        return data;
    }

    /**
     * @brief Default solver routine (Newton) and strategy (Fixed).
     * 
     * @param target 
     * @param params 
     * @return Data 
     */
    Data solver(const Target &target, const Parameters &params) {
        return solver(target, params, newton_routine, fixed_strategy);
    }

    /**
     * @brief Newton routine.
     * 
     * @param data 
     * @return Vector 
     */
    Vector newton_routine(const Data &data) {
        // X_{k + 1} = X_k - Alpha_k * Df(X_k).
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

        // X_{k + 1} = X_k - Alpha_k * Df(X_k) + Eta(X_k - X_{k - 1}).
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

        // y = X_k + Eta(X_k - X_{k - 1}).
        // X_{k + 1} = y - Alpha_k * Df(y).
        Vector partial = data.current + strategy_eta * (data.current - data.previous);
        return partial - data.size * data.target.gradient(partial);
    }

    /**
     * @brief Fixed Alpha strategy.
     * 
     * @param data 
     * @param params 
     * @return Real 
     */
    Real fixed_strategy(const Data &data, const Parameters &params) {
        return data.size;
    }

    /**
     * @brief Exponential decay strategy.
     * 
     * @param data 
     * @param params 
     * @return Real 
     */
    Real exponential_strategy(const Data &data, const Parameters &params) {
        // Alpha_{k + 1} = Alpha_0 * exp(- Mu * K).
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
        // Alpha_{k + 1} = Alpha_0 / (1 + Mu * K).
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

    /**
     * @brief Prints the results of a single run.
     * 
     * @param result 
     */
    void show(const Data &result) {
        std::cout << "\nMinimum at: " << result.next << std::endl;

        if(result.status)
            std::cout << "Converged in " << result.index + 1 << " steps." << std::endl;
        else
            std::cout << "Not converged :(" << std::endl;
    }

    /**
     * @brief Prints the results of a single run and compares to the exact result.
     * 
     * @param result 
     */
    void show(const Data &result, const Vector &exact) {
        std::cout << "\nMinimum at: " << result.next << std::endl;
        std::cout << "\nDistance: " << (result.next - exact).norm() << std::endl;

        if(result.status)
            std::cout << "Converged in " << result.index + 1 << " steps." << std::endl;
        else
            std::cout << "Not converged :(" << std::endl;
    }

}