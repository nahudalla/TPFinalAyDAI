#ifndef TPFINALAYDAI_ALGOR_STACK_HPP
#define TPFINALAYDAI_ALGOR_STACK_HPP

#include <algor/List.hpp>

namespace algor {
    template <typename T>
    class Stack : private List<T> {
    public:
        void push(T value) {
            this->add_front(std::move(value));
        }
        bool isEmpty() const {
            return List<T>::isEmpty();
        }
        bool hasNextToTop() const {
            auto it = this->begin();
            auto end = this->end();

            return it != end && ++it != end;
        }
        const T & top() const {
            return *(this->begin());
        }
        const T & nextToTop() const {
            return *(++(this->begin()));
        }
        T pop() {
            return this->remove(this->begin());
        }
    };
}

#endif //TPFINALAYDAI_ALGOR_STACK_HPP