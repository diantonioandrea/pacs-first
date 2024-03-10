/**
 * @file Vector.cpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Vector.hpp"

// Norm.
#include <cmath>

namespace pacs {

    /**
     * @brief Construct a new Vector object.
     * 
     */
    Vector::Vector(): size(1) {
        // Initializes an empty 1D vector.
        this->elements.clear();
        this->elements.resize(1);
    }

    /**
     * @brief Construct a new Vector object of a given size.
     * 
     * @param N 
     */
    Vector::Vector(const size_t &N): size(N) {
        // Initializes an empty vector.
        #ifndef NDEBUG
        assert(N > 0);
        #endif

        this->elements.clear();
        this->elements.resize(N);

        for(auto &elements_it: this->elements) {
            elements_it = 0.0L;
        }
    }

    /**
     * @brief Construct a new Vector object from a given vector.
     * 
     * @param vector 
     */
    Vector::Vector(const Vector &vector): size(vector.size) {
        // Initializes a vector from a vector.
        this->elements.clear();
        this->elements.resize(this->size);

        auto values_it = vector.elements.begin();
        for(auto &elements_it: this->elements) {
            elements_it = static_cast<Real>(*values_it++);
        }
    }

    /**
     * @brief Vector copy.
     * 
     * @param vector 
     * @return Vector& 
     */
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

    /**
     * @brief Const [] access operator.
     * 
     * @param index 
     * @return Real 
     */
    Real Vector::operator [](const size_t &index) const {
        #ifndef NDEBUG
        assert(index < this->size);
        #endif

        return this->elements[index];
    }

    /**
     * @brief [] access operator.
     * 
     * @param index 
     * @return Real& 
     */
    Real &Vector::operator [](const size_t &index) {
        #ifndef NDEBUG
        assert(index < this->size);
        #endif

        return this->elements[index];
    }

    /**
     * @brief Dot product.
     * 
     * @param vector 
     * @return Real 
     */
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

    /**
     * @brief Euclidean norm.
     * 
     * @return Real 
     */
    Real Vector::norm() const {
        return std::sqrt(this->dot(*this));
    }

    /**
     * @brief Unary + operator.
     * 
     * @return Vector 
     */
    Vector Vector::operator +() const {
        return *this;
    }

    /**
     * @brief Unary - operator.
     * 
     * @return Vector 
     */
    Vector Vector::operator -() const {
        Vector result = Vector(this->size);

        auto elements_it = this->elements.begin();

        for(auto &result_it: result.elements) {
            result_it = -(*elements_it++);
        }

        return result;
    }

    /**
     * @brief + operator.
     * 
     * @param vector 
     * @return Vector 
     */
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

    /**
     * @brief - operator.
     * 
     * @param vector 
     * @return Vector 
     */
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

    /**
     * @brief += operator.
     * 
     * @param vector 
     * @return Vector& 
     */
    Vector &Vector::operator +=(const Vector &vector) {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        return *this = *this + vector;
    }

    /**
     * @brief -= operator.
     * 
     * @param vector 
     * @return Vector& 
     */
    Vector &Vector::operator -=(const Vector &vector) {
        #ifndef NDEBUG
        assert(this->size == vector.size);
        #endif

        return *this = *this - vector;
    }

    /**
     * @brief << operator.
     * 
     * @param ost 
     * @param vector 
     * @return std::ostream& 
     */
    std::ostream &operator <<(std::ostream &ost, const Vector &vector) {
        ost << "(";

        for(size_t j = 0; j < vector.size - 1; ++j) {
            ost << vector.elements[j] << ", ";
        }

        return ost << vector.elements[vector.size - 1] << ")";
    }
    
}