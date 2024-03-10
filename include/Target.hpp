/**
 * @file Target.hpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TARGET_PACS
#define TARGET_PACS

#include "Vector.hpp"

namespace pacs {

    using Function = Real (*) (const Vector &);
    using Gradient = Vector (*) (const Vector &);

    /**
     * @brief Target function and gradient struct.
     * 
     */
    struct Target {
        Target(Function);
        Target(Function, Gradient);
        
        Function function;
        Gradient gradient;

        Vector operator ()(const Vector &) const;
    };

}

#endif