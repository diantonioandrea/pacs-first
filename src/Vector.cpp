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
        assert(N > 0);

        this->elements.clear();
        this->elements.resize(N);
    }

    // Copy (=).
    Vector &Vector::operator =(const Vector &vector) {
        assert(this->size == vector.size);

        auto values_it = vector.elements.begin();
        for(auto &elements_it: this->elements) {
            elements_it = static_cast<Real>(*values_it++);
        }

        return *this;
    }

    // Access.
    Real Vector::operator [](const size_t &index) const {
        assert(index < this->size);

        return this->elements[index];
    }

    Real &Vector::operator [](const size_t &index) {
        assert(index < this->size);

        return this->elements[index];
    }

    // Methods.
    Real Vector::dot(const Vector &vector) const {
        assert(this->size == vector.size);

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
        assert(this->size == vector.size);
        Vector result = Vector(this->size);

        auto values_it = vector.elements.begin();
        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) + static_cast<Real>(*values_it++);
        }

        return result;
    }

    Vector Vector::operator -(const Vector &vector) const {
        assert(this->size == vector.size);
        Vector result = Vector(this->size);

        auto values_it = vector.elements.begin();
        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) - static_cast<Real>(*values_it++);
        }

        return result;
    }

    Vector &Vector::operator +=(const Vector &vector) {
        assert(this->size == vector.size);

        return *this = *this + vector;
    }

    Vector &Vector::operator -=(const Vector &vector) {
        assert(this->size == vector.size);

        return *this = *this - vector;
    }

    // Output.
    std::ostream &operator <<(std::ostream &ost, const Vector &vector) {
        ost << "(";

        for(size_t j = 0; j < vector.size - 1; ++j) {
            ost << vector.elements[j] << ", ";
        }

        ost << vector.elements[vector.size - 1];

        return ost << ")";
    }
}