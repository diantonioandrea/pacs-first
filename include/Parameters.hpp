/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef PARAMETERS_PACS
#define PARAMETERS_PACS

#include <iostream>

#include "Vector.hpp"

namespace pacs {

    /**
     * @brief Parameters structure.
     * 
     */
    struct Parameters {
        Vector start = Vector(2);
        Real alpha = 1.0E-1L;
        Real step_tolerance = 1.0E-6L;
        Real residual_tolerance = 1.0E-6L;
        size_t max_iterations = 10000;
        Real strategy_mu = 0.2L;
        Real strategy_sigma = 0.25L;
    };
    
    Parameters read_json(const std::string &, const bool &);
    std::ostream &operator <<(std::ostream &, const Parameters &);
}

#endif