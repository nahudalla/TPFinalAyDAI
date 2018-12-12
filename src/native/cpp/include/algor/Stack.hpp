#ifndef TPFINALAYDAI_ALGOR_STACK_HPP
#define TPFINALAYDAI_ALGOR_STACK_HPP

#include <algor/List.hpp>

#ifndef __EMSCRIPTEN__
#include <iostream>
#endif

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

        bool operator==(const Stack & rhs) {
            if(this == &rhs) return true;

            return static_cast<List<T> &>(*this) == static_cast<const List<T>>(rhs);
        }

        bool operator!=(const Stack & rhs) {
            return !(*this == rhs);
        }

#ifndef __EMSCRIPTEN__
        friend std::ostream &operator<<(std::ostream & out, Stack const& stack) {
            Stack reversed;

            auto it = stack.list.begin();
            auto end = stack.list.end();
            for(; it!=end; ++it) {
                reversed.push(*it);
            }

            return out << reversed.list;
        }
#endif
    };
}

#endif //TPFINALAYDAI_ALGOR_STACK_HPP
