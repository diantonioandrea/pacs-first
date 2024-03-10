/**
 * @file Differential.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Differential.hpp"

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
    
}