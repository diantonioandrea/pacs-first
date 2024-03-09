/**
 * @file Default.hpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEFAULT_PACS
#define DEFAULT_PACS

#include <iostream>

#include "Vector.hpp"

namespace pacs {

    Real target_func(const Vector &x);
    Vector target_grad(const Vector &x);

}

#endif