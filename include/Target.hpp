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
     * @brief Target function and gradient class.
     * 
     */
    class Target {
        private:
            const Function target_function;
            const Gradient target_gradient;

        public:
            Target(Function);
            Target(Function, Gradient);

            Real function(const Vector &) const;
            Vector gradient(const Vector &) const;
    };

}

#endif