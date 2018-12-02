#ifndef TPFINALAYDAI_RBTREE_HPP
#define TPFINALAYDAI_RBTREE_HPP

#include <algorithm>

namespace algor {
    template <typename T>
    class RBTree;

    namespace __detail_RBTree {
        enum Color {RED, BLACK};

        template <typename T>
        class Node {
            Node * left, * right, * parent;
            Color color = BLACK;

            void rotate_left(Node * & root) {
                Node * y = this->right;

                this->right = y->left;

                if(!y->left->isNil()) {
                    y->left->parent = this;
                }

                y->parent = this->parent;

                if(this->parent->isNil()) {
                    root = y;
                } else if(*this == *(this->parent->left)) {
                    this->parent->left = y;
                } else {
                    this->parent->right = y;
                }

                y->left= this;
                this->parent = y;
            }

            void rotate_right(Node * & root) {
                Node * y = this->left;

                this->left= y->right;

                if(!y->right->isNil()) {
                    y->right->parent = this;
                }

                y->parent = this->parent;

                if(this->parent->isNil()) {
                    root = y;
                } else if(*this == *(this->parent->left)) {
                    this->parent->left = y;
                } else {
                    this->parent->right = y;
                }

                y->right= this;
                this->parent = y;
            }

            void insert_fixup(Node * & root) {
                Node * z = this;
                while(z->parent->color == RED) {
                    if(*(z->parent) == *(z->parent->parent->left)) {
                        Node * y = z->parent->parent->right;
                        if(y->color == RED) {
                            z->parent->color = BLACK;
                            y->color = BLACK;
                            z->parent->parent->color = RED;
                            z = z->parent->parent;
                        } else {
                            if(*z == *(z->parent->right)) {
                                z = z->parent;
                                z->rotate_left(root);
                            }
                            z->parent->color = BLACK;
                            z->parent->parent->color = RED;
                            z->parent->parent->rotate_right(root);
                        }
                    } else {
                        Node * y = z->parent->parent->left;
                        if(y->color == RED) {
                            z->parent->color = BLACK;
                            y->color = BLACK;
                            z->parent->parent->color = RED;
                            z = z->parent->parent;
                        } else {
                            if(*z == *(z->parent->left)) {
                                z = z->parent;
                                z->rotate_right(root);
                            }
                            z->parent->color = BLACK;
                            z->parent->parent->color = RED;
                            z->parent->parent->rotate_left(root);
                        }
                    }
                }

                root->color = BLACK;
            }

            void transplant_to(Node * & root, Node * to) {
                if(to->parent->isNil()) {
                    root = this;
                } else if(*to == *(to->parent->left)) {
                    to->parent->left = this;
                } else to->parent->right = this;

                this->parent = to->parent;
            }

            void remove_fixup(Node * & root) {
                Node * x = this;
                while(*x != *root && x->color == BLACK) {
                    if(*x == *(x->parent->left)) {
                        Node * w = x->parent->right;
                        if(w->color == RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            x->parent->rotate_left(root);
                            w = x->parent->right;
                        }
                        if(w->left->color == BLACK && w->right->color == BLACK) {
                            w->color = RED;
                            x = x->parent;
                        } else {
                            if(w->right->color == BLACK) {
                                w->left->color = BLACK;
                                w->color = RED;
                                w->rotate_right(root);
                                w = x->parent->right;
                            }
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->right->color = BLACK;
                            x->parent->rotate_left(root);
                            x = root;
                        }
                    } else {
                        Node * w = x->parent->left;
                        if(w->color == RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            x->parent->rotate_right(root);
                            w = x->parent->left;
                        }
                        if(w->right->color == BLACK && w->left->color == BLACK) {
                            w->color = RED;
                            x = x->parent;
                        } else {
                            if(w->left->color == BLACK) {
                                w->right->color = BLACK;
                                w->color = RED;
                                w->rotate_left(root);
                                w = x->parent->left;
                            }
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->left->color = BLACK;
                            x->parent->rotate_right(root);
                            x = root;
                        }
                    }
                }
                x->color = BLACK;
            }
        public:
            Node(Node * parent, Node * left, Node * right, Color color = BLACK)
                : parent(parent), left(left), right(right), color(color)
            {}

            Node() : parent(Nil::get()), left(Nil::get()), right(Nil::get())
            {}

            Node(Node const& other) {
                *this = other;
            }
            Node(Node &&) noexcept = default;
            Node &operator=(Node const& other) {
                if(this != &other) {
                    this->~Node();
                    this->left = other.left->clone();
                    this->right = other.right->clone();
                    this->left->parent = this;
                    this->right->parent = this;
                    this->color = other.color;
                }
                return *this;
            }
            Node &operator=(Node &&) noexcept = default;
            ~Node() {
                delete this->left; this->left = nullptr;
                delete this->right; this->right = nullptr;
                this->parent = nullptr;
            }

            virtual T * getData() const = 0;
            virtual Node * clone() const = 0;

            Node *getLeft() const {
                return left;
            }

            void setLeft(Node *left) {
                Node::left = left;
            }

            Node *getRight() const {
                return right;
            }

            void setRight(Node *right) {
                Node::right = right;
            }

            Node *getParent() const {
                return parent;
            }

            void setParent(Node *parent) {
                Node::parent = parent;
            }

            Color getColor() const {
                return color;
            }

            void setColor(Color color) {
                Node::color = color;
            }

            bool operator==(const Node &rhs) const {
                return parent == rhs.parent &&
                       left == rhs.left &&
                       right == rhs.right &&
                       color == rhs.color &&
                       this->getData() == rhs.getData();
            }

            bool operator!=(const Node &rhs) const {
                return !(rhs == *this);
            }

            bool isNil() const {
                return this == Nil::get();
            }

            Node * search(T const& data) const {
                Node * current = this;
                T * current_data;

                while (!current->isNil() && !(*(current_data = current->getData()) == data)) {
                    if(*current_data < data) current = current->right;
                    else current = current->left;
                }

                return current;
            }

            Node * minimum() const {
                Node * min = this;

                while(!min->left->isNil()) min = min->left;

                return min;
            }

            Node * maximum() const {
                Node * max = this;

                while(!max->right->isNil()) max = max->right;

                return max;
            }

            Node * next() const {
                if(!this->right->isNil()) {
                    return this->right->minimum();
                }

                Node * current = this;
                Node * successor = this->parent;

                while (!successor->isNil() && *current == *(successor->right)) {
                    current = successor;
                    successor = successor->parent;
                }

                return successor;
            }

            Node * previous() const {
                if(!this->left->isNil()) {
                    return this->left->maximum();
                }

                Node * current = this;
                Node * predecessor = this->parent;

                while (!predecessor->isNil() && *current == *(predecessor->left)) {
                    current = predecessor;
                    predecessor = predecessor->parent;
                }

                return predecessor;
            }

            void insert(Node * & root) {
                Node * y = Node::Nil::get();
                Node * x = root;

                while(!x->isNil()) {
                    y = x;
                    if(*(this->getData()) < *(x->getData())) x = x->left;
                    else x = x->right;
                }

                this->parent = y;

                if(y->isNil()) root = this;
                else if(*(this->getData()) < *(y->getData())) y->left = this;
                else y->right = this;

                this->left = Node::Nil::get();
                this->right = Node::Nil::get();
                this->color = RED;

                this->insert_fixup(root);
            }

            void remove(Node * & root) {
                Node * z = this;
                Node * y = z;
                Node * x;
                auto y_original_color = y->color;

                if(z->left->isNil()) {
                    x = z->right;
                    z->right->transplant_to(root, z);
                } else if(z->right->isNil()) {
                    x = z->left;
                    z->left->transplant_to(root, z);
                } else {
                    y = z->right->minimum();
                    y_original_color = y->color;
                    x = y->right;
                    if(*(y->parent) == *z) {
                        x->parent = y;
                    } else {
                        y->right->transplant_to(root, y);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    y->transplant_to(root, z);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }
                if(y_original_color == BLACK) {
                    x->remove_fixup(root);
                }
            }

            class Nil : public Node {
                Nil() {
                    this->setParent(this);
                    this->setLeft(this);
                    this->setRight(this);
                    this->setColor(BLACK);
                }

            public:
                T *getData() const override { return nullptr; }

                Node * clone() const override {
                    return this;
                }

                static Node * get() {
                    static Node * nil = new Nil();

                    return nil;
                }
            };
        };

        template <typename T>
        class DataNode : public Node<T> {
            T data;

        public:
            explicit DataNode(T data) {
                this->data = std::move(data);
            }

            DataNode(T data, Node<T> * parent, Node<T> * left, Node<T> * right, Color color)
                : Node<T>(parent, left, right, color), DataNode(std::move(data))
            {}

            DataNode(DataNode const&) = default;
            DataNode(DataNode &&) noexcept = default;
            DataNode &operator=(DataNode const&) = default;
            DataNode &operator=(DataNode &&) noexcept = default;
            ~DataNode() = default;

            Node<T> *clone() const override {
                return new DataNode(*this);
            }

            T *getData() const override {
                return &this->data;
            }
        };

        template <typename T>
        class Iterator {
            typedef Node<T> Node;

            Node * node = Node::Nil::get();

            explicit Iterator(Node * node) : node(node)
            {}

            friend class RBTree<T>;
        public:
            Iterator() = default;
            Iterator(Iterator const&) = default;
            Iterator(Iterator &&) noexcept = default;
            Iterator &operator=(Iterator const&) = default;
            Iterator &operator=(Iterator &&) noexcept = default;
            ~Iterator() = default;

            bool isDereferentiable() const {
                // TODO: test
                return node->getData() != nullptr;
            }

            operator bool() const {
                return this->isDereferentiable();
            }

            T &operator*() {
                // TODO: test
                return *(this->node->getData());
            }

            T const&operator*() const {
                // TODO: test
                return *(this->node->getData());
            }

            Iterator &next() {
                // TODO: test
                this->node = this->node->next();

                return *this;
            }

            Iterator operator++() {
                // TODO: test
                Iterator tmp = *this;
                this->next();
                return tmp;
            }

            Iterator &operator++(int) {
                // TODO: test
                return this->next();
            }

            Iterator &previous() {
                // TODO: test
                this->node = this->node->previous();

                return *this;
            }

            Iterator operator--() {
                // TODO: test
                Iterator tmp = *this;
                this->previous();
                return tmp;
            }

            Iterator &operator--(int) {
                // TODO: test
                return this->previous();
            }

            bool operator==(const Iterator &rhs) const {
                // TODO: test
                return *node == *(rhs.node);
            }

            bool operator!=(const Iterator &rhs) const {
                // TODO: test
                return !(rhs == *this);
            }
        };
    }

    template <typename T>
    class RBTree {
        typedef __detail_RBTree::Node<T> Node;
        typedef __detail_RBTree::DataNode<T> DataNode;

        Node * root = Node::getNil();
    public:
        typedef __detail_RBTree::Iterator<T> Iterator;

        RBTree(RBTree const& other) {*this = other;} // TODO: test
        RBTree(RBTree &&) noexcept = default; // TODO: test
        RBTree &operator=(RBTree const& other) {
            // TODO: test
            if(this != &other) {
                this->~RBTree();
                this->root = other.root->clone();
            }
            return *this;
        }
        RBTree &operator=(RBTree &&) noexcept = default; // TODO: test
        ~RBTree() {
            // TODO: test
            delete this->root; this->root = nullptr;
        }

        Iterator minimum() const {
            // TODO: test
            return Iterator(this->root->minimum());
        }

        Iterator maximum() const {
            // TODO: test
            return Iterator(this->root->maximum());
        }

        Iterator search(T const& value) const {
            // TODO: test
            return Iterator(this->root->search(value));
        }

        Iterator insert(T value) {
            // TODO: test
            Node * node = new DataNode(value);
            node->insert(this->root);

            return Iterator(node);
        }

        void remove(Iterator const& it) {
            // TODO: test
            it.node->remove(this->root);
        }

        Iterator begin() {
            // TODO: test
            return Iterator(this->root);
        }

        Iterator end() {
            // TODO: test
            return Iterator(Node::Nil::get());
        }

        const Iterator cbegin() const {
            // TODO: test
            return Iterator(this->root);
        }

        const Iterator cend() const {
            // TODO: test
            return Iterator(Node::Nil::get());
        }
    };
}

#endif //TPFINALAYDAI_RBTREE_HPP
