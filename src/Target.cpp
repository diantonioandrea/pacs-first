/**
 * @file Target.cpp
 * @author Andrea Di Antonio 
 * 
 * @date 2024-03-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Target.hpp"
#include "../include/Differential.hpp"

namespace pacs {

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
     * @brief Copies a Target object.
     * 
     * @param target 
     * @return Target& 
     */
    Target &Target::operator =(const Target &target) {
        this->target_function = target.target_function;
        this->target_gradient = target.target_gradient;

        return *this;
    }

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