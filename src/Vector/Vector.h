#ifndef H_VECTOR
#define H_VECTOR
#include <algorithm>
#include <utility>
#include <exception>
#include <stdexcept>

namespace vector {

	template<class S>
	class Vector {

    private:

        int size;
        int capacity;
        S *arr;

    public:

        /**
         * @brief Default constructor: construct vector with zero size and capacity equal to five
         */
        Vector() : size(0), capacity(5) {

            arr = new S[capacity];
        }
        /**
         * @brief Constructor with  capacity: construct vector with given capacity and zero size
         * @param capacity Vector capacity
         * @throw invalid_argument with "Vector capacity need be positive" if you call constructor with negative value
         */
        explicit Vector(int capacity) : size(0) {

            if (capacity < 0)
                throw std::invalid_argument("Vector capacity need be positive");
            else if (capacity == 0) {
                this->capacity = 5;
                arr = new S[capacity];
            } else {
                arr = new S[capacity]();
                this->capacity = capacity;
            }
        }
        /**
         * @brief Copy constructor
         * @param vector Reference to vector with which parameters you want to create new vector
         */
        Vector(const Vector<S>& vector) {

            arr = new S[vector.capacity];
            std::copy(vector.arr, vector.arr + vector.size, arr);
            capacity = vector.capacity;
            size = vector.size;
        }
        /**
         * @brief Move constructor
         * @param vector Rvalue reference to vector which parameters will be used to create new vector
         */
        Vector(Vector<S> &&vector) noexcept : size(vector.size), capacity(vector.capacity), arr(vector.arr) {

            vector.size = 0;
            vector.capacity = 0;
            vector.arr = nullptr;
        }
        /**
         * @brief Destructor: frees used memory
         */
        ~Vector() {

            delete[] arr;
        }

        /**
         * @brief Method required to add new element to the end of vector
         * @param value Const reference to object you want to add to vector
         */
        void pushback(const S &value) {

            if (size < capacity) {
                *(arr + size) = std::move(value);
                ++size;
            } else {

                S *tmp = new S[capacity * 2];
                std::copy(arr, arr + size, tmp);
                capacity *= 2;
                delete[] arr;
                arr = tmp;
                *(arr + size) = std::move(value);
                ++size;

            }
        }
        /**
         * @brief Return vector to default state with zero size and capacity equal to five
         */
        void clear() {

            S *tmp = new S[5];
            delete[] arr;
            arr = tmp;
            capacity = 5;
            size = 0;

        }

        /**
         * @brief Method required to get size of vector
         * @return Size of vector
         */
        int getSize() const {

            return size;
        }
        /**
         * @brief Method required to get vector capacity
         * @return Vector capacity
         */
        int getCapacity() const {

            return capacity;
        }
        /**
         * @brief Copy assignment operator
         * @param vector Const reference to vector you want to copy
         * @return Copy of vector
         */
        Vector<S> &operator=(const Vector<S> &vector) {

            if (this != &vector) {
                S *tmp = new S[vector.capacity];
                std::copy(vector.arr, vector.arr + vector.size, tmp);
                delete[] arr;
                arr = tmp;
                capacity = vector.capacity;
                size = vector.size;
            }
            return *this;
        }
        /**
         * @brief Move assignment operator
         * @param vector Rvalue reference to vector which parameters you want to use
         * @return Copy of vector
         */
        Vector<S> &operator=(Vector<S> &&vector)  noexcept {

            std::swap(size, vector.size);
            std::swap(capacity, vector.capacity);
            std::swap(arr, vector.arr);
            return *this;
        }
        /**
         * @brief Reloadeds [] operator required to get element from vector
         * @param index Index of element in vector, may change from 0 to "size - 1"
         * @return Reference to element you need
         * @throw invalid_argument with "Incorrect index" if you call it with negative parameter or with parameter which
         * bigger then "size - 1"
         */
        S& operator[](int index) {

            if (index < size && index >= 0)
                return *(arr + index);
            else
                throw std::invalid_argument("Incorrect index");
        }
        /**
         * @brief Reloaded [] operator for const vectors required to get element from vector
         * @param index Index of element in vector, may change from 0 to "size - 1"
         * @return Const reference to element you need
         * @throw invalid_argument with "Incorrect index" if you call it with negative parameter or with parameter which
         * bigger then "size - 1"
         */
        const S& operator[](int index) const {

            if (index < size && index >= 0)
                return *(arr + index);
            else
                throw std::invalid_argument("Incorrect index");
        }
    };
}
#endif
//� ���� �����//