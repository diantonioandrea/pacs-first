/**
 * @file Target.hpp
 * @author Andrea Di Antonio 
 * 
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
            Function target_function;
            Gradient target_gradient;

        public:
            Target(Function);
            Target(Function, Gradient);

            Target &operator =(const Target &);

            Real function(const Vector &) const;
            Vector gradient(const Vector &) const;
    };

}

#endif