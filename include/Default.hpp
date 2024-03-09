/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef DEFAULT_PACS
#define DEFAULT_PACS

#include <iostream>

// Real type and vectors.
#include "Vector.hpp"

namespace pacs {

    // Default targets.
    Real target_func(const Vector &x);
    Vector target_grad(const Vector &x);

}

#endif