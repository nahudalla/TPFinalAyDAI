#ifndef TPFINALAYDAI_LSIT_IMPL_ITERATOR_HPP
#define TPFINALAYDAI_LSIT_IMPL_ITERATOR_HPP

#include <algorithm>

#include <algor/List_impl/Node.hpp>
#include <algor/List_impl/ConstIterator.hpp>

namespace algor {
    template <typename> class List;
}

namespace algor::__detail__List {
    template <typename T>
    class Iterator : public ConstIterator<T, Node<T>> {
        typedef Node<T> Node;
        typedef ConstIterator<T, Node> Base;

        Iterator(Node *prev, Node *curr) : Base(prev, curr) {}

        friend class List<T>;

    public:
        Iterator() = default;

        Iterator(Iterator const &) = default;
        Iterator(Iterator &&) noexcept = default;
        Iterator &operator=(Iterator const &) = default;
        Iterator &operator=(Iterator &&) noexcept = default;
        ~Iterator() = default;

        explicit Iterator(const Base & other) : Base(other) {}

        Iterator &next() {
            Base::next();
            return *this;
        }

        Iterator &operator++() {
            this->next();
            return *this;
        }

        const Iterator operator++(int) {
            auto tmp = *this;
            this->next();
            return std::move(tmp);
        }

        T &operator*() {
            return this->curr->elem;
        }

    };
}

#endif //TPFINALAYDAI_LSIT_IMPL_ITERATOR_HPP
