/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#include "../include/Solver.hpp"
#include <iostream>

namespace pacs {

    // SOLVERS.

    // Newton.
    std::pair<Vector, bool> newton_solver(const Target &target, const Parameters &parameters, Real (*strategy) (const Solver_Data &, const Parameters &)) {
        size_t dimension = parameters.start.get_size();

        Vector point = Vector(dimension);
        Vector next = Vector(dimension);
        Vector gradient_point = Vector(dimension);

        Real step_size = parameters.alpha;
        point = parameters.start;

        // Return value.
        std::pair<Vector, bool> result = {Vector(dimension), true};

        // Solver's data.
        Solver_Data data{target, Vector(dimension), 0};

        for(size_t k = 0; k < parameters.max_iter; ++k) {
            gradient_point = target.target_gradient(point);
            next = point - (step_size * gradient_point);

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

            point = next;

            data.step = k;
            data.point = next;

            step_size = strategy(data, parameters);
        }

        result.first = next;
        result.second = false;

        return result;
    }

    // STRATEGIES.

    // Exponential.
    Real exponential_strategy(const Solver_Data &data, const Parameters &parameters) {
        return parameters.alpha * std::exp(- parameters.strategy_mu * static_cast<Real>(data.step));
    }

    // Inverse.
    Real inverse_strategy(const Solver_Data &data, const Parameters &parameters) {
        return parameters.alpha / (1.0L + parameters.strategy_mu * static_cast<Real>(data.step));
    }

    // Armijo.
    Real armijo_strategy(const Solver_Data &data, const Parameters &parameters) {
        // Traget function evaluated at x_k.
        Real target_point = data.target.target_function(data.point);
        
        // Traget gradient evaluated at x_k.
        Vector gradient_point = Vector(data.point.get_size());
        gradient_point = data.target.target_gradient(data.point);

        // Next step size.
        Real step_size = parameters.alpha;

        while(target_point - data.target.target_function(data.point - step_size * gradient_point) < parameters.strategy_sigma * step_size * std::pow(gradient_point.norm(), 2)) {
            step_size /= 2.0L;
        }

        return step_size;
    }

}