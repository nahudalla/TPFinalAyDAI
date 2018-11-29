#ifndef TPFINALAYDAI_LIST_HPP
#define TPFINALAYDAI_LIST_HPP

namespace algor {
    template<typename T>
    class List {
        struct Node {
            T elem;
            Node *next;
        };

        Node *first = nullptr;
        Node *last = nullptr;
    public:
        class Iterator;

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

        void sort() {
            auto curr = this->begin();
            auto end = this->end();
            while (curr != end) {
                auto it = curr;
                it.next();

                while (it != end) {
                    if (*it < *curr) {
                        this->swap(it, curr);
                    }

                    it.next();
                }

                curr.next();
            }
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
