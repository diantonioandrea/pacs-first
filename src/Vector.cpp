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

    // Operations.
    Vector Vector::operator +(const Vector &operand) const {
        assert(this->size == operand.size);
        Vector result = Vector(this->size);

        auto values_it = operand.elements.begin();
        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) + static_cast<Real>(*values_it++);
        }

        return result;
    }

    Vector Vector::operator -(const Vector &operand) const {
        assert(this->size == operand.size);
        Vector result = Vector(this->size);

        auto values_it = operand.elements.begin();
        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) - static_cast<Real>(*values_it++);
        }

        return result;
    }

    Vector Vector::operator *(const std::floating_point auto &operand) const {
        Vector result = Vector(this->size);

        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) * static_cast<Real>(operand);
        }

        return result;
    }

    Vector Vector::operator /(const std::floating_point auto &operand) const {
        Vector result = Vector(this->size);
        
        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = (*elements_it++) / static_cast<Real>(operand);
        }

        return result;
    }

    Vector Vector::operator *(const std::integral auto &operand) const {
        return *this * static_cast<Real>(operand);
    }

    Vector Vector::operator /(const std::integral auto &operand) const {
        return *this / static_cast<Real>(operand);
    }

    Vector &Vector::operator +=(const Vector &operand) {
        assert(this->size == operand.size);

        return *this = *this + operand;
    }

    Vector &Vector::operator -=(const Vector &operand) {
        assert(this->size == operand.size);

        return *this = *this - operand;
    }

    Vector &Vector::operator *=(const std::integral auto &operand) {
        return *this = *this * operand;
    }

    Vector &Vector::operator /=(const std::integral auto &operand) {
        return *this = *this / operand;
    }

    Vector &Vector::operator *=(const std::floating_point auto &operand) {
        return *this = *this * operand;
    }

    Vector &Vector::operator /=(const std::floating_point auto &operand) {
        return *this = *this / operand;
    }


}