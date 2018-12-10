#ifndef TPFINALAYDAI_ARRAY_HPP
#define TPFINALAYDAI_ARRAY_HPP

#include <cstddef>
#include <initializer_list>
#include <algorithm>

namespace algor {
    template <typename T>
    class Array {
        T * data = nullptr;
        std::size_t _size = 0;

    public:
        explicit Array(std::size_t size) : _size(size) {
            this->data = new T[size];
        }
        Array(std::initializer_list<T> list) : Array(list.size()) {
            auto it = list.begin();
            auto end = list.end();
            for(std::size_t i = 0; it != end; ++it, ++i) {
                this->data[i] = std::move(*it);
            }
        }
        Array &operator=(std::initializer_list<T> list) {
            this->~Array();
            this->Array(std::move(list));

            return *this;
        }

        Array(Array const& other) {*this=other;}
        Array(Array && other) noexcept {*this=std::move(other);}
        ~Array() {
            delete[] this->data;
            this->data = nullptr;
            this->_size = 0;
        }

        Array &operator=(Array const& other) {
            if(this != &other) {
                this->~Array();
                this->Array(other._size);
                for (int i = 0; i < other._size; ++i) {
                    this->data[i] = other.data[i];
                }
            }

            return *this;
        }
        Array &operator=(Array && other) noexcept {
            if(this != &other) {
                this->~Array();
                std::swap(this->data, other.data);
                std::swap(this->_size, other._size);
            }

            return *this;
        }

        std::size_t size() const {
            return this->_size;
        }

        T &operator[](std::size_t i) {
            return this->data[i];
        }
        const T&operator[](std::size_t i) const {
            return this->data[i];
        }
    };
}

#endif //TPFINALAYDAI_ARRAY_HPP
