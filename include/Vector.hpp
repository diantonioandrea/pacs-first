/* 
PACS - First Challenge.
Andrea Di Antonio, 10655477.
*/

#ifndef VECTOR_PACS
#define VECTOR_PACS

// Assertions.
#include <cassert>

// std::vector.
#include <vector>

// For constructors.
#include <initializer_list>
#include <concepts>

// Math.
#include <cmath>

// Output.
#include <iostream>

// Real type.
#include "Type.hpp"

namespace pacs {

    // Real vectors.
    class Vector {
        private:
            const size_t size;
            std::vector<Real> elements;

        public:
            
            // CONSTRUCTORS and COPY.

            // Constructors.
            Vector();
            Vector(const size_t &);
            Vector(const Vector &);

            // Concept constructors.
            template<std::floating_point type>
            Vector(const size_t &N, const std::vector<type> &values): size(N) {
                // Initializes a vector from a std::vector.
                #ifndef NDEBUG
                assert(N > 0);
                assert(N == values.size());
                #endif

                // Clears and resizes the elements vector.
                this->elements.clear(); // Probably useless.
                this->elements.resize(N);

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            template<std::integral type>
            Vector(const size_t &N, const std::vector<type> &values): size(N) {
                // Initializes a vector from an integral std::vector.
                #ifndef NDEBUG
                assert(N > 0);
                assert(N == values.size());
                #endif

                this->elements.clear();
                this->elements.resize(N);

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            template<std::floating_point type>
            Vector(const size_t &N, const std::initializer_list<type> &values): size(N) {
                // Initializes a vector from a std::initializer_list.
                #ifndef NDEBUG
                assert(N > 0);
                assert(N == values.size());
                #endif

                this->elements.clear();
                this->elements.resize(N);

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            template<std::integral type>
            Vector(const size_t &N, const std::initializer_list<type> &values): size(N) {
                // Initializes a vector from an integral std::initializer_list.
                #ifndef NDEBUG
                assert(N > 0);
                assert(N == values.size());
                #endif

                this->elements.clear();
                this->elements.resize(N);

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }
            
            template<std::floating_point type, size_t M>
            Vector(const size_t &N, const std::array<type, M> &values): size(N) {
                // Initializes a vector from a std::array.
                #ifndef NDEBUG
                assert(N > 0);
                assert(N == M);
                #endif

                this->elements.clear();
                this->elements.resize(N);

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            template<std::integral type, size_t M>
            Vector(const size_t &N, const std::array<type, M> &values): size(N) {
                // Initializes a vector from an integral std::array.
                #ifndef NDEBUG
                assert(N > 0);
                assert(N == M);
                #endif

                this->elements.clear();
                this->elements.resize(N);

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            // Copy (=).
            Vector &operator =(const Vector &);

            // Methods which copy values from the following structures into this->elements.
            // Behave in a similar fashion as previous constructors.
            template<std::floating_point type>
            Vector &operator =(const std::vector<type> &values) {
                #ifndef NDEBUG
                assert(this->size == values.size());
                #endif
                
                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }

                return *this;
            }

            template<std::integral type>
            Vector &operator =(const std::vector<type> &values) {
                #ifndef NDEBUG
                assert(this->size == values.size());
                #endif
                
                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }

                return *this;
            }

            template<std::floating_point type>
            Vector &operator =(const std::initializer_list<type> &values) {
                #ifndef NDEBUG
                assert(this->size == values.size());
                #endif
                
                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }

                return *this;
            }

            template<std::integral type>
            Vector &operator =(const std::initializer_list<type> &values) {
                #ifndef NDEBUG
                assert(this->size == values.size());
                #endif
                
                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }

                return *this;
            }

            template<std::floating_point type, size_t M>
            Vector &operator =(const std::array<type, M> &values) {
                #ifndef NDEBUG
                assert(this->size == M);
                #endif
                
                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }

                return *this;
            }

            template<std::integral type, size_t M>
            Vector &operator =(const std::array<type, M> &values) {
                #ifndef NDEBUG
                assert(this->size == M);
                #endif
                
                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }

                return *this;
            }

            // Access.
            Real operator [](const size_t &) const;
            Real &operator [](const size_t &);

            // METHODS.
            Real dot(const Vector &) const;
            Real norm() const;
            
            // OPERATIONS.

            // Unary operations.
            Vector operator +() const;
            Vector operator -() const;

            // Binary operations.

            // Vector sums.
            Vector operator +(const Vector &) const;
            Vector operator -(const Vector &) const;
            Vector &operator +=(const Vector &);
            Vector &operator -=(const Vector &);

            // Scalar products.
            Vector operator *(const std::floating_point auto &operand) const {
                Vector result = Vector(this->size);

                auto elements_it = this->elements.begin();

                for(auto &result_it: result.elements) {
                    result_it = (*elements_it++) * static_cast<Real>(operand);
                }

                return result;
            }

            Vector operator /(const std::floating_point auto &operand) const {
                Vector result = Vector(this->size);
                
                auto elements_it = this->elements.begin();

                for(auto &result_it: result.elements) {
                    result_it = (*elements_it++) / static_cast<Real>(operand);
                }

                return result;
            }

            Vector operator *(const std::integral auto &operand) const {
                return *this * static_cast<Real>(operand);
            }

            Vector operator /(const std::integral auto &operand) const {
                return *this / static_cast<Real>(operand);
            }

            Vector &operator *=(const std::integral auto &operand) {
                return *this = *this * operand;
            }

            Vector &operator /=(const std::integral auto &operand) {
                return *this = *this / operand;
            }

            Vector &operator *=(const std::floating_point auto &operand) {
                return *this = *this * operand;
            }

            Vector &operator /=(const std::floating_point auto &operand) {
                return *this = *this / operand;
            }

            friend Vector operator *(const std::integral auto &operand, const Vector &vector) {
                return vector * static_cast<Real>(operand);
            }

            friend Vector operator *(const std::floating_point auto &operand, const Vector &vector) {
                return vector * static_cast<Real>(operand);
            }
            
            // Constexpr methods.
            constexpr size_t length() const {
                return this->size;
            }

            // Output.
            friend std::ostream &operator <<(std::ostream &, const Vector &);
    };

}

#endif