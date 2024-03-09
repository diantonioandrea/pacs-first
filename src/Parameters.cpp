/**
 * @file Parameters.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Parameters.hpp"

#include <string>
#include <fstream>

#include "../include/json.hpp"

namespace pacs {
    
    /**
     * @brief Reads parameters from a JSON file.
     * 
     * @param filename 
     * @param verbose 
     * @return Parameters 
     */
    Parameters read_json(std::string const &filename, const bool &verbose) {

        // Default and return values.
        Parameters defaults, returns;

        // File check.
        std::ifstream file(filename);
        if(!(file)) {
            if(verbose)
                std::cout << "\nLoaded default parameters:\n" << defaults;

            return defaults;
        }

        // Reads JSON from the opened file.
        nlohmann::json json_file;
        file >> json_file;

        // Search for values.
        returns.start = json_file.value("start", defaults.start.get_elements());
        returns.alpha = json_file.value("alpha", defaults.alpha);
        returns.step_tolerance = json_file.value("step_tolerance", defaults.step_tolerance);
        returns.residual_tolerance = json_file.value("residual_tolerance", defaults.residual_tolerance);
        returns.max_iterations = json_file.value("max_iterations", defaults.max_iterations);
        returns.strategy_mu = json_file.value("strategy_mu", defaults.strategy_mu);
        returns.strategy_sigma = json_file.value("strategy_sigma", defaults.strategy_sigma);

        if(verbose)
            std::cout << "\nLoaded:\n" << returns;

        return returns;
    }

    /**
     * @brief Prints a parameters struct.
     * 
     * @param ost 
     * @param params 
     * @return std::ostream& 
     */
    std::ostream &operator <<(std::ostream &ost, const Parameters &params) {
        ost << "\tstart: " << params.start << std::endl;

        ost << "\talpha: " << params.alpha << std::endl;

        ost << "\tstep_tolerance: " << params.step_tolerance << std::endl;
        ost << "\tresidual_tolerance: " << params.residual_tolerance << std::endl;

        ost << "\tmax_iterations: " << params.max_iterations << std::endl;

        ost << "\tstrategy_mu: " << params.strategy_mu << std::endl;
        ost << "\tstrategy_sigma: " << params.strategy_sigma << std::endl;

        return ost;
    }
}