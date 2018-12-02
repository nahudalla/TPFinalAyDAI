#ifndef TPFINALAYDAI_LIST_HPP
#define TPFINALAYDAI_LIST_HPP

#include <algor/Comparator.hpp>

namespace algor {
    template<typename T>
    class List {
    public:
        class Iterator;

    private:
        struct Node {
            T elem;
            Node *next;
        };

        Node *first = nullptr;
        Node *last = nullptr;

        void merge(Comparator<T> const& cmp, Iterator & a_begin, Iterator b, Iterator & end) {
            // IMPORTANTE: Los iteradores a_begin y end DEBEN ser actualizados para que apunten
            // a los nuevos nodos de inicio y fin de la lista ordenada

            Iterator a = a_begin;

            while(a != b && b != end) {
                if(cmp.compare(*a, *b) > 0) {
                    // Incremento b antes de modificarlo para no perder el siguiente
                    auto b_next = b; b_next.next();

                    // Saco b de su lugar
                    b.prev->next = b.curr->next;

                    // Actualizo iteradores
                    b_next.prev = b.prev;
                    if(b_next == end) end.prev = b.prev;

                    // Si b es el último, actualizo el puntero al último elemento de la lista
                    if(b.curr->next == nullptr) {
                        this->last = b.prev;
                    }

                    // Pongo b antes que a
                    if(a.prev == nullptr) {
                        this->first = b.curr;
                    } else {
                        a.prev->next = b.curr;
                    }
                    b.curr->next = a.curr;

                    // Actualizo iteradores
                    b.prev = a.prev;
                    if(a == a_begin) {
                        a_begin = b;
                    }
                    a.prev = b.curr;

                    // Incremento el iterador de b
                    b = b_next;
                } else {
                    a.next();
                }
            }
        }

        Iterator find_middle(Iterator begin, Iterator const& end) {
            Iterator slow = std::move(begin);
            Iterator fast = slow; fast.next();

            while(fast != end) {
                fast.next();
                if(fast != end) {
                    slow.next();
                    fast.next();
                }
            }

            slow.next();

            return std::move(slow);
        }

        void merge_sort(Comparator<T> const& cmp, Iterator & begin, Iterator & end) {
            // Si hay menos de dos elementos, ya está ordenada
            {
                Iterator next;
                if (begin == end || ((next = begin), next.next()), next == end) return;
            }

            // Split (Divide)
            Iterator a_end = this->find_middle(begin, end);

            // Sort
            this->merge_sort(cmp, begin, a_end);
            this->merge_sort(cmp, a_end, end);

            // Merge (Conquer)
            this->merge(cmp, begin, a_end, end);
        }
    public:
        List() = default;

        ~List() {
            while (first != nullptr) {
                auto *tmp = first;
                first = first->next;
                delete tmp;
            }
        }

        void add(const T &elem) {
            // Creo un nuevo nodo
            Node *node = new Node{elem, nullptr};

            // Si no hay último elemento, la lista está vacía
            if (this->last == nullptr) {
                // Inicializo la lista con el nuevo nodo
                this->first = this->last = node;
            } else {
                // La lista tiene elementos, lo agrego al final
                this->last->next = node;
                // Pongo el elemento nuevo como el ultimo
                this->last = node;
            }
        }

        int length() const {
            Node *current = this->first; // Inicializo el nodo actual como el primero
            int counter = 0; // Inicializo el contador en cero

            while (current != nullptr) { // Mientras que haya nodo actual
                counter++; // Aumento el contador
                current = current->next; // Me muevo al siguiente
            }

            return counter;
        }

        Iterator begin() {
            return Iterator(nullptr, this->first);
        }

        Iterator end() {
            return Iterator(nullptr, nullptr);
        }

        const Iterator cbegin() const {
            // TODO: test
            return Iterator(nullptr, this->first);
        }

        const Iterator cend() const {
            // TODO: test
            return Iterator(nullptr, nullptr);
        }

        void remove(Iterator &it) {
            auto next = it.curr->next;

            if (it.prev != nullptr) it.prev->next = next;

            delete it.curr;

            if (this->first == it.curr) this->first = next;
            if (this->last == it.curr) this->last = it.prev;

            it.curr = next;
        }

        bool isEmpty() const {
            return this->first == nullptr && this->last == nullptr;
        }

        void swap(Iterator &e1, Iterator &e2) {
            if (!e1 || !e2) return;

            auto e1_prev = e1.prev;
            auto e1_curr = e1.curr;
            auto e2_prev = e2.prev;
            auto e2_curr = e2.curr;

            if (e1_curr->next == nullptr) this->last = e2_curr;
            if (e2_curr->next == nullptr) this->last = e1_curr;

            if (e1_prev != nullptr) e1_prev->next = e2_curr;
            else this->first = e2_curr;

            if (e2_prev != nullptr) e2_prev->next = e1_curr;
            else this->first = e1_curr;

            auto tmp = e1_curr->next;
            e1_curr->next = e2_curr->next;
            e2_curr->next = tmp;

            e1.curr = e2_curr;
            e2.curr = e1_curr;
        }

        void sort(Comparator<T> const& cmp = Comparator<T>()) {
            auto b = this->begin();
            auto e = this->end();
            this->merge_sort(cmp, b, e);
        }

        class Iterator {
            Node *prev = nullptr;
            Node *curr = nullptr;

            Iterator(Node *prev, Node *curr) : prev(prev), curr(curr) {}

            friend class List<T>;

        public:
            Iterator() = default;

            Iterator(Iterator const &) = default;

            Iterator(Iterator &&) noexcept = default;

            Iterator &operator=(Iterator const &) = default;

            Iterator &operator=(Iterator &&) noexcept = default;

            ~Iterator() = default;

            Iterator &next() {
                if (curr != nullptr) {
                    prev = curr;
                    curr = curr->next; // Si hay nodo actual, me muevo al siguiente
                }

                return *this;
            }

            Iterator operator++() {
                Iterator tmp = *this;
                this->next();
                return tmp;
            }

            Iterator &operator++(int) {
                return this->next();
            }

            bool isDereferentiable() const {
                // Devuelve verdadero si el elemento actual no es nulo
                return curr != nullptr;
            }

            operator bool() const {
                return this->isDereferentiable();
            }

            T &operator*() {
                return curr->elem;
            }

            T const&operator*() const {
                // TODO: test
                return curr->elem;
            }

            bool operator==(const Iterator &rhs) const {
                return curr == rhs.curr;
            }

            bool operator!=(const Iterator &rhs) const {
                return !(rhs == *this);
            }
        };
    };
}

#endif //TPFINALAYDAI_LIST_HPP
