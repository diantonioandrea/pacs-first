#include "../include/Parameters.hpp"

// Files.
#include <string>
#include <fstream>

// JSON.
#include "../include/json.hpp"

namespace pacs {
    // Reading parameters from a JSON file.
    Parameters read_json(std::string const &filename) {

        // Default and return values.
        Parameters defaults, returns;

        // File check.
        std::ifstream file(filename);
        if(!(file)) {
            return defaults;
        }

        // Reads JSON from the opened file.
        nlohmann::json json_file;
        file >> json_file;

        // Search for values.
        returns.alpha = json_file.value("alpha", defaults.alpha);
        returns.step_tolerance = json_file.value("step_tolerance", defaults.step_tolerance);
        returns.residual_tolerance = json_file.value("residual_tolerance", defaults.residual_tolerance);
        returns.max_iterations = json_file.value("max_iterations", defaults.max_iterations);
        returns.strategy_mu = json_file.value("strategy_mu", defaults.strategy_mu);
        returns.strategy_sigma = json_file.value("strategy_sigma", defaults.strategy_sigma);

        return returns;
    }

    // Parameters output.
    std::ostream &operator <<(std::ostream &ost, const Parameters &params) {
        ost << "start: " << params.start << std::endl;

        ost << "alpha: " << params.alpha << std::endl;

        ost << "step_tolerance: " << params.step_tolerance << std::endl;
        ost << "residual_tolerance: " << params.residual_tolerance << std::endl;

        ost << "max_iterations: " << params.max_iterations << std::endl;

        ost << "strategy_mu: " << params.strategy_mu << std::endl;
        ost << "strategy_sigma: " << params.strategy_sigma << std::endl;

        return ost;
    }
}