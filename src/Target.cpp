/**
 * @file Target.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Target.hpp"

namespace pacs {

    /**
     * @brief Evaluates the numerical gradient at a given point.
     * 
     * @param function 
     * @param x 
     * @return Vector 
     */
    Vector numerical_gradient(Function function, const Vector &x) {
        Real step = 1.0E-4L;
        Vector gradient = Vector(x.get_size());

        for(size_t k = 0; k < gradient.get_size(); ++k) {
            Vector direction = Vector(x.get_size());
            direction[k] = step;

            gradient[k] = (function(x + direction) - function(x)) / step;
        }

        return gradient;
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
        return this->target_function(x);
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

        return numerical_gradient(this->target_function, x);
    }

}