#include "../include/Default.hpp"

namespace pacs {

    // Default functions definition.
    Real target_func(const Vector &x) {
        #ifndef NDEBUG
        assert(x.length() == 2);
        #endif

        return x[0] * x[1] + 4 * std::pow(x[0], 4) + std::pow(x[1], 2) + 3 * x[0];
    }

    Vector target_grad(const Vector &x) {
        #ifndef NDEBUG
        assert(x.length() == 2);
        #endif

        Vector gradient = Vector(2);

        gradient[0] = x[1] + 16.0L * std::pow(x[0], 3) + 3.0L;
        gradient[1] = x[0] + 2.0L * x[1];

        return gradient;
    }

}