#include "../include/Vector.hpp"

namespace pacs {

    // Vector.

    // Simple constrcutors.
    Vector::Vector(): size(1) {
        // Initializes an empty 1D vector.
        this->elements.clear();
        this->elements.resize(1);
    }

    Vector::Vector(const size_t &N): size(N) {
        // Initializes an empty vector.
        assert(N > 0);

        this->elements.clear();
        this->elements.resize(N);
    }

}