#ifndef TPFINALAYDAI_CONSTITERATOR_HPP
#define TPFINALAYDAI_CONSTITERATOR_HPP

#include <algorithm>

#include <algor/List_impl/Node.hpp>

namespace algor {
    template <typename> class List;
}

namespace algor::__detail__List {
    template <typename T, typename Node = const Node<T>>
    class ConstIterator {
        Node *prev = nullptr;

    protected:
        Node *curr = nullptr;

        ConstIterator(Node *prev, Node *curr) : prev(prev), curr(curr) {}

        friend class List<T>;

    public:
        ConstIterator() = default;

        ConstIterator(ConstIterator const &) = default;
        ConstIterator(ConstIterator &&) noexcept = default;
        ConstIterator &operator=(ConstIterator const &) = default;
        ConstIterator &operator=(ConstIterator &&) noexcept = default;
        ~ConstIterator() = default;

        ConstIterator &next() {
            if (this->curr != nullptr) {
                this->prev = this->curr;
                this->curr = this->curr->next; // Si hay nodo actual, me muevo al siguiente
            }

            return *this;
        }

        ConstIterator &operator++() {
            this->next();
            return *this;
        }

        const ConstIterator operator++(int) {
            auto tmp = *this;
            this->next();
            return std::move(tmp);
        }

        bool isDereferentiable() const {
            // Devuelve verdadero si el elemento actual no es nulo
            return this->curr != nullptr;
        }

        operator bool() const {
            return this->isDereferentiable();
        }

        const T &operator*() const {
            return this->curr->elem;
        }

        bool operator==(const ConstIterator &rhs) const {
            return this->curr == rhs.curr;
        }

        bool operator!=(const ConstIterator &rhs) const {
            return !(rhs == *this);
        }
    };
}

#endif //TPFINALAYDAI_CONSTITERATOR_HPP
