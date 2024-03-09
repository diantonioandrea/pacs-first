/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
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