/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

// Standard library.
#include <iostream>
#include <vector>

// PACS headers.
#include "include/Types.hpp"
#include "include/Vector.hpp"
#include "include/Parameters.hpp"
#include "include/Solver.hpp"

int main(int argc, char **argv) {
    pacs::Target target;
    pacs::Parameters parameters;

    std::cout << pacs::solver(target, parameters, pacs::newton_routine, pacs::exponential_strategy).first << std::endl;
    std::cout << pacs::solver(target, parameters, pacs::newton_routine, pacs::inverse_strategy).first << std::endl;
    std::cout << pacs::solver(target, parameters, pacs::newton_routine, pacs::armijo_strategy).first << std::endl;

    std::cout << pacs::solver(target, parameters, pacs::hb_routine, pacs::exponential_strategy).first << std::endl;
    std::cout << pacs::solver(target, parameters, pacs::hb_routine, pacs::inverse_strategy).first << std::endl;
    std::cout << pacs::solver(target, parameters, pacs::hb_routine, pacs::armijo_strategy).first << std::endl;

    std::cout << pacs::solver(target, parameters, pacs::nesterov_routine, pacs::exponential_strategy).first << std::endl;
    std::cout << pacs::solver(target, parameters, pacs::nesterov_routine, pacs::inverse_strategy).first << std::endl;
    std::cout << pacs::solver(target, parameters, pacs::nesterov_routine, pacs::armijo_strategy).first << std::endl;

    return 0;
}