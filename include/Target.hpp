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

#include <muParser.h>

#include <Vector.hpp>
#include <Parameters.hpp>

namespace pacs {

    // Aliases.
    using Function = Real (*) (const Vector &);
    using Gradient = Vector (*) (const Vector &);

    /**
     * @brief Target function and gradient class.
     * 
     */
    class Target {
        private:
            mutable Vector point;
            
            const Function target_function;
            const Gradient target_gradient;
            
            mutable mu::Parser target_parser;

        public:
            Target(const Parameters &);
            Target(Function);
            Target(Function, Gradient);

            Real function(const Vector &) const;
            Vector gradient(const Vector &) const;
    };

}

#endif