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

    std::cout << pacs::newton_solver(target, parameters, pacs::exponential_strategy).first << std::endl;
    std::cout << pacs::newton_solver(target, parameters, pacs::inverse_strategy).first << std::endl;
    std::cout << pacs::newton_solver(target, parameters, pacs::armijo_strategy).first << std::endl;

    return 0;
}