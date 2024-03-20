/**
 * @file Target.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Target.hpp>

namespace pacs {
    
    /**
     * @brief Construct a new Target object from the parameters (MuParser).
     * 
     * @param str 
     */
    Target::Target(const Parameters &params): point{params.guess}, target_function{nullptr}, target_gradient{nullptr} {
        try {
            for(unsigned int j = 0; j < this->point.get_size(); ++j) {
                std::string variable = "x" + std::to_string(j);

                this->target_parser.DefineVar(variable, &this->point[j]);
            }

            this->target_parser.SetExpr(params.parser);
        } catch(mu::Parser::exception_type &e) {
            std::cerr << e.GetMsg() << std::endl;
        }
    }

    /**
     * @brief Construct a new Target object from a given function.
     * 
     * @param function 
     */
    Target::Target(Function function): target_function{function}, target_gradient{nullptr} {}

    /**
     * @brief Construct a new Target object from a given function and its gradient.
     * 
     * @param function 
     * @param gradient 
     */
    Target::Target(Function function, Gradient gradient): target_function{function}, target_gradient{gradient} {}

    /**
     * @brief Evaluates the function at a given X.
     * 
     * @param x 
     * @return Real 
     */
    Real Target::function(const Vector &x) const {
        if(this->target_function)
            return this->target_function(x);

        // MuParser function definition.
        this->point = x;
        return static_cast<Real>(this->target_parser.Eval());
    }

    /**
     * @brief Evaluates the gradient at a given X.
     * 
     * @param x 
     * @return Vector 
     */
    Vector Target::gradient(const Vector &x) const {
        if(this->target_gradient)
            return this->target_gradient(x);

        // Numerical gradient by finite differences.
        Real step = 1.0E-4L;
        Vector gradient = Vector(x.get_size());

        Real point_evaluation, direction_evaluation;

        for(std::size_t k = 0; k < gradient.get_size(); ++k) {
            Vector direction = Vector(x.get_size());
            direction[k] = step;

            if(this->target_function) {

                // Standard function definition.
                point_evaluation = this->target_function(x);
                direction_evaluation = this->target_function(x + direction);
            } else {

                // MuParser function definition.
                this->point = x;
                point_evaluation = this->target_parser.Eval();

                this->point += direction;
                direction_evaluation = this->target_parser.Eval();
            }

            // k-th partial derivative.
            gradient[k] = (direction_evaluation - point_evaluation) / step;
        }

        return gradient;
    }

}