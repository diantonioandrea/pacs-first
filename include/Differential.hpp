/**
 * @file Differential.hpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DIFFERENTIAL_PACS
#define DIFFERENTIAL_PACS

#include "Vector.hpp"
#include "Target.hpp"

namespace pacs {

    Vector numerical_gradient(Function, const Vector &);

    /**
     * @brief Numerical function and gradient functor.
     * 
     */
    struct NTarget {
        Function function;
        Vector operator ()(const Vector &x) const;
    };

}

#endif