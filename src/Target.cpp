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
#include "../include/Differential.hpp"

namespace pacs {

    /**
     * @brief Construct a new Target object from a given function.
     * 
     * @param function 
     */
    Target::Target(Function function): function{function}, gradient{nullptr} {}

    /**
     * @brief Construct a new Target object from a given function and its gradient.
     * 
     * @param function 
     * @param gradient 
     */
    Target::Target(Function function, Gradient gradient): function{function}, gradient{gradient} {}

    /**
     * @brief Evaluates the function at a given X.
     * 
     * @param x 
     * @return Real 
     */
    Real Target::func_eval(const Vector &x) const {
        return this->function(x);
    }

    /**
     * @brief Evaluates the gradient at a given X.
     * 
     * @param x 
     * @return Vector 
     */
    Vector Target::grad_eval(const Vector &x) const {
        if(this->gradient != nullptr)
            return this->gradient(x);

        return numerical_gradient(this->function, x);
    }

}