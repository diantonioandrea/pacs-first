/**
 * @file Parameters.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Parameters.hpp>

#include <string>
#include <fstream>
#include <cassert>

#include <json.hpp>

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
        Parameters defaults;

        // File check.
        std::ifstream file(filename);
        if(!(file)) {
            if(verbose)
                std::cout << "\nLoaded default parameters:\n" << defaults;

            return defaults;
        }

        // Reads JSON from the opened file.
        nlohmann::json js;
        file >> js;

        // Search for values.
        Parameters returns{js.value("guess", defaults.guess.get_elements())};
        
        returns.alpha = js.value("alpha", defaults.alpha);
        returns.step_tolerance = js.value("step_tolerance", defaults.step_tolerance);
        returns.residual_tolerance = js.value("residual_tolerance", defaults.residual_tolerance);
        returns.max_iterations = js.value("max_iterations", defaults.max_iterations);
        returns.parser = js.value("parser", defaults.parser);
        returns.strategy_mu = js.value("strategy_mu", defaults.strategy_mu);
        returns.strategy_sigma = js.value("strategy_sigma", defaults.strategy_sigma);

        if(verbose)
            std::cout << "\nLoaded:\n" << returns;

        // Checks.
        assert(returns.alpha > 0.0L);
        assert(returns.step_tolerance > 0.0L);
        assert(returns.residual_tolerance > 0.0L);
        assert(returns.max_iterations > 0);
        assert(returns.strategy_mu > 0);
        assert(returns.strategy_sigma > 0);
        assert(returns.strategy_sigma < 0.5);

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
        ost << "\tguess: " << params.guess << std::endl;

        ost << "\talpha: " << params.alpha << std::endl;

        ost << "\tstep_tolerance: " << params.step_tolerance << std::endl;
        ost << "\tresidual_tolerance: " << params.residual_tolerance << std::endl;

        ost << "\tmax_iterations: " << params.max_iterations << std::endl;

        ost << "\tparser: " << params.parser << std::endl;

        ost << "\tstrategy_mu: " << params.strategy_mu << std::endl;
        ost << "\tstrategy_sigma: " << params.strategy_sigma << std::endl;

        return ost;
    }
}