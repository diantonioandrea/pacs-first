/**
 * @file Vector.hpp
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef VECTOR_PACS
#define VECTOR_PACS

// Assertions.
#include <cassert>

// Constructors.
#include <vector>
#include <array>
#include <initializer_list>
#include <concepts>

// Output.
#include <iostream>

namespace pacs {

    using Real = long double;

    /**
     * @brief Vector class.
     * 
     */
    class Vector {
        private:
            const size_t size;
            std::vector<Real> elements;

        public:
            Vector();
            Vector(const size_t &);
            Vector(const Vector &);

            /**
             * @brief Construct a new Vector object from a floating point std::vector.
             * 
             * @tparam type 
             * @param values 
             */
            template<std::floating_point type>
            Vector(const std::vector<type> &values): size(values.size()) {
                // Initializes a vector from a std::vector.
                // Clears and resizes the elements vector.
                this->elements.clear(); // Probably useless.
                this->elements.resize(values.size());

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }
            
            /**
             * @brief Construct a new Vector object from an integral std::vector.
             * 
             * @tparam type 
             * @param values 
             */
            template<std::integral type>
            Vector(const std::vector<type> &values): size(values.size()) {
                // Initializes a vector from an integral std::vector.
                this->elements.clear();
                this->elements.resize(values.size());

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            /**
             * @brief Construct a new Vector object from a floating-point std::initializer_list.
             * 
             * @tparam type 
             * @param values 
             */
            template<std::floating_point type>
            Vector(const std::initializer_list<type> &values): size(values.size()) {
                // Initializes a vector from a std::initializer_list.
                this->elements.clear();
                this->elements.resize(values.size());

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }
            
            /**
             * @brief Construct a new Vector object from an integral std::initializer_list.
             * 
             * @tparam type 
             * @param values 
             */
            template<std::integral type>
            Vector(const std::initializer_list<type> &values): size(values.size()) {
                // Initializes a vector from an integral std::initializer_list.
                this->elements.clear();
                this->elements.resize(values.size());

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }
            
            /**
             * @brief Construct a new Vector object from a floating-point std::array.
             * 
             * @tparam type 
             * @param values 
             */
            template<std::floating_point type, size_t M>
            Vector(const std::array<type, M> &values): size(values.size()) {
                // Initializes a vector from a std::array.
                this->elements.clear();
                this->elements.resize(values.size());

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            /**
             * @brief Construct a new Vector object from an integral std::array.
             * 
             * @tparam type 
             * @param values 
             */
            template<std::integral type, size_t M>
            Vector(const std::array<type, M> &values): size(values.size()) {
                // Initializes a vector from an integral std::array.
                this->elements.clear();
                this->elements.resize(values.size());

                auto values_it = values.begin();
                for(auto &elements_it: this->elements) {
                    elements_it = static_cast<Real>(*values_it++);
                }
            }

            Vector &operator =(const Vector &);

            /**
             * @brief Copy operator from a floating-point std::vector.
             * 
             * @tparam type 
             * @param values 
             * @return Vector& 
             */
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
            
            /**
             * @brief Copy operator from an integral std::vector.
             * 
             * @tparam type 
             * @param values 
             * @return Vector& 
             */
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

            /**
             * @brief Copy operator from a floating-point std::initializer_list.
             * 
             * @tparam type 
             * @param values 
             * @return Vector& 
             */
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

            /**
             * @brief Copy operator from an integral std::initializer_list.
             * 
             * @tparam type 
             * @param values 
             * @return Vector& 
             */
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

            /**
             * @brief Copy operator from a floating-point std::array.
             * 
             * @tparam type 
             * @param values 
             * @return Vector& 
             */
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

            /**
             * @brief Copy operator from an integral std::array.
             * 
             * @tparam type 
             * @param values 
             * @return Vector& 
             */
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

            Real operator [](const size_t &) const;
            Real &operator [](const size_t &);

            Real dot(const Vector &) const;
            Real norm() const;
            
            Vector operator +() const;
            Vector operator -() const;

            Vector operator +(const Vector &) const;
            Vector operator -(const Vector &) const;
            Vector &operator +=(const Vector &);
            Vector &operator -=(const Vector &);

            /**
             * @brief Scalar product.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector operator *(const std::floating_point auto &operand) const {
                Vector result = Vector(this->size);

                auto elements_it = this->elements.begin();

                for(auto &result_it: result.elements) {
                    result_it = (*elements_it++) * static_cast<Real>(operand);
                }

                return result;
            }
            
            /**
             * @brief Scalar division.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector operator /(const std::floating_point auto &operand) const {
                Vector result = Vector(this->size);
                
                auto elements_it = this->elements.begin();

                for(auto &result_it: result.elements) {
                    result_it = (*elements_it++) / static_cast<Real>(operand);
                }

                return result;
            }

            /**
             * @brief Operator *.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector operator *(const std::integral auto &operand) const {
                return *this * static_cast<Real>(operand);
            }

            /**
             * @brief Operator /.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector operator /(const std::integral auto &operand) const {
                return *this / static_cast<Real>(operand);
            }

            /**
             * @brief Operator *=.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector &operator *=(const std::integral auto &operand) {
                return *this = *this * operand;
            }

            /**
             * @brief Operator /=.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector &operator /=(const std::integral auto &operand) {
                return *this = *this / operand;
            }

            /**
             * @brief Operator *=.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector &operator *=(const std::floating_point auto &operand) {
                return *this = *this * operand;
            }

            /**
             * @brief Operator /=.
             * 
             * @param operand 
             * @return Vector 
             */
            Vector &operator /=(const std::floating_point auto &operand) {
                return *this = *this / operand;
            }

            /**
             * @brief Friend operator *.
             * 
             * @param operand 
             * @return Vector 
             */
            friend Vector operator *(const std::integral auto &operand, const Vector &vector) {
                return vector * static_cast<Real>(operand);
            }

            /**
             * @brief Friend operator *.
             * 
             * @param operand 
             * @return Vector 
             */
            friend Vector operator *(const std::floating_point auto &operand, const Vector &vector) {
                return vector * static_cast<Real>(operand);
            }
            
            /**
             * @brief Returns the size of the Vector.
             * 
             * @return constexpr size_t 
             */
            constexpr size_t get_size() const {
                return this->size;
            }
            
            /**
             * @brief Returns the elements of the Vector.
             * 
             * @return std::vector<Real> 
             */
            std::vector<Real> get_elements() const {
                return this->elements;
            }

            friend std::ostream &operator <<(std::ostream &, const Vector &);
    };

}

#endif