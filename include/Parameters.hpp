/**
 * @file Parameters.hpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef PARAMETERS_PACS
#define PARAMETERS_PACS

#include <iostream>
#include <vector>
#include <string>

#include <Vector.hpp>

namespace pacs {

    /**
     * @brief Parameters class.
     * 
     */
    class Parameters {
        public:
            Parameters() {}

            // Needed as pacs::Vector.size is a constant.
            Parameters(const std::vector<Real> &vector): guess{vector} {}

            Vector guess = Vector(2);
            Real alpha = 1.0E-1L;
            Real step_tolerance = 1.0E-6L;
            Real residual_tolerance = 1.0E-6L;
            std::size_t max_iterations = 10000;
            std::string parser = "x0 * x1 + 4 * x0 * x0 * x0 * x0 + x1 * x1 + 3 * x0";
            Real strategy_mu = 0.2L;
            Real strategy_sigma = 0.25L;
    };
    
    Parameters read_json(const std::string &, const bool &);
    std::ostream &operator <<(std::ostream &, const Parameters &);
}

#endif