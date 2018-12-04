#ifndef TPFINALAYDAI_ITERATOR_HPP
#define TPFINALAYDAI_ITERATOR_HPP

#include <algor/RBTree_impl/Node.hpp>
#include <algor/RBTree_impl/ConstIterator.hpp>

namespace algor {
    template <typename T>
    class RBTree;
}

namespace algor::__detail_RBTree {
    template <typename T, bool reverse = false>
    class Iterator : public ConstIterator<T, Node<T>, reverse> {
        explicit Iterator(Node<T> * node) : ConstIterator<T, Node<T>>(node)
        {}

        friend class RBTree<T>;

    public:
        Iterator() = default;
        Iterator(Iterator const&) = default;
        Iterator(Iterator &&) noexcept = default;
        Iterator &operator=(Iterator const&) = default;
        Iterator &operator=(Iterator &&) noexcept = default;
        ~Iterator() = default;

        explicit Iterator(IteratorBase<T, Node<T>> const& other)
                : ConstIterator<T, Node<T>, reverse>(other)
        {}

        T &operator*() {
            return *(this->node->getData());
        }
    };

    template <typename T>
    using ReverseIterator = Iterator<T, true>;
}

#endif //TPFINALAYDAI_ITERATOR_HPP
