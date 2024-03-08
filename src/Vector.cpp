/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

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
        #ifndef NDEBUG
        assert(N > 0);
        #endif

        this->elements.clear();
        this->elements.resize(N);
    }

    Vector::Vector(const Vector &vector): size(vector.size) {
        // Initializes a vector from a vector.
        this->elements.clear();
        this->elements.resize(this->size);

        auto values_it = vector.elements.begin();
        for(auto &elements_it: this->elements) {
            elements_it = static_cast<Real>(*values_it++);
        }
    }

    // Copy (=).
    Vector &Vector::operator =(const Vector &vector) {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        auto values_it = vector.elements.begin();
        for(auto &elements_it: this->elements) {
            elements_it = static_cast<Real>(*values_it++);
        }

        return *this;
    }

    // Access.
    Real Vector::operator [](const size_t &index) const {
        #ifndef NDEBUG
        assert(index < this->size);
        #endif

        return this->elements[index];
    }

    Real &Vector::operator [](const size_t &index) {
        #ifndef NDEBUG
        assert(index < this->size);
        #endif

        return this->elements[index];
    }

    // Methods.
    Real Vector::dot(const Vector &vector) const {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        Real result = 0.0L;

        auto values_it = vector.elements.begin();
        for(auto &elements_it: this->elements) {
            result += elements_it * *values_it++;
        }

        return result;
    }

    Real Vector::norm() const {
        return std::sqrt(this->dot(*this));
    }

    // Unary operations.
    Vector Vector::operator +() const {
        return *this;
    }

    Vector Vector::operator -() const {
        Vector result = Vector(this->size);

        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = -(*elements_it++);
        }

        return result;
    }


    // Operations.
    Vector Vector::operator +(const Vector &vector) const {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        Vector result = Vector(this->size);

        auto values_it = vector.elements.begin();
        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) + static_cast<Real>(*values_it++);
        }

        return result;
    }

    Vector Vector::operator -(const Vector &vector) const {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        Vector result = Vector(this->size);

        auto values_it = vector.elements.begin();
        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) - static_cast<Real>(*values_it++);
        }

        return result;
    }

    Vector &Vector::operator +=(const Vector &vector) {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        return *this = *this + vector;
    }

    Vector &Vector::operator -=(const Vector &vector) {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        return *this = *this - vector;
    }

    // Output.
    std::ostream &operator <<(std::ostream &ost, const Vector &vector) {
        ost << "(";

        for(size_t j = 0; j < vector.size - 1; ++j) {
            ost << vector.elements[j] << ", ";
        }

        return ost << vector.elements[vector.size - 1] << ")";
    }
    
}