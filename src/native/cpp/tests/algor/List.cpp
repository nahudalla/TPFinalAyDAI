#include "../Test.hpp"

#include <algor/List.hpp>
#include <random>

using algor::List;

bool list_create(); ADD_TEST(LIST_CREATE, list_create);
bool list_empty(); ADD_TEST(LIST_EMPTY, list_empty);
bool list_length(); ADD_TEST(LIST_LENGTH, list_length);
bool list_iterator(); ADD_TEST(LIST_ITERATOR, list_iterator);
bool list_iterator_basic_equality(); ADD_TEST(LIST_ITERATOR_BASIC_EQUALITY, list_iterator_basic_equality);
bool list_iterator_copy(); ADD_TEST(LIST_ITERATOR_COPY, list_iterator_copy);
bool list_iterator_equality(); ADD_TEST(LIST_ITERATOR_EQUALITY, list_iterator_equality);
bool list_modify_element(); ADD_TEST(LIST_MODIFY_ELEMENT, list_modify_element);
bool list_remove_element(); ADD_TEST(LIST_REMOVE_ELEMENT, list_remove_element);
bool list_swap(); ADD_TEST(LIST_SWAP, list_swap);
bool list_sort(); ADD_TEST(LIST_SORT, list_sort);

List<int> create_list(int cant);
bool is_ordered(List<int> & list, int cant);

bool list_create() {
    for (int i = 0; i < 10; ++i) {
        create_list(i);
    }

    return true;
}

bool list_empty() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);

        if(list.isEmpty() && i != 0) return false;
    }

    return true;
}

bool list_length() {
    for (int i = 0; i < 10; ++i) {
        List<int> list = create_list(i);

        const auto l = list.length();

        if(l != i) return false;
    }

    return true;
}

bool list_iterator() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);

        auto it = list.begin();

        for (int j = 0; j < i; ++j) {
            if(!it.isDereferentiable() || *it != j) return false;
            it.next();
        }

        if(it.isDereferentiable()) return false;
    }

    return true;
}

bool list_iterator_basic_equality() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);
        auto it = list.begin();
        auto it2 = list.begin();
        for (int j = 0; j < i; ++j) {
            if(it != it2) return false;
            it.next();
            it2.next();
        }
        if(it != list.end()) return false;
    }

    return true;
}

bool list_iterator_copy() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);

        auto it = list.begin();
        auto end = list.end();

        decltype(it) it2;

        while(it != end) {
            it2 = it;
            if(it2 != it) return false;
            it.next();
        }
    }
    return true;
}

bool list_iterator_equality() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);
        auto it = list.begin();

        if(i != 0) {
            List<int>::Iterator iterators[i];
            for (int j = 0; j < i; ++j) {
                iterators[j] = it;
                it.next();
            }

            it = list.begin();
            auto end = list.end();
            int count = 0;
            while(it != end) {
                for (int k = 0; k < i; ++k) {
                    if (count == k) {
                        if (iterators[k] != it) return false;
                    } else {
                        if (iterators[k] == it) return false;
                    }
                }
                it.next();
                count++;
            }
        }

        if(it != list.end()) return false;
    }

    return true;
}

bool list_modify_element() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);
        auto it = list.begin();
        auto end = list.end();

        while(it != end) {
            *it += 7;
            it.next();
        }

        it = list.begin();
        for (int j = 0; j < i; ++j, it.next()) {
            if(*it != 7+j) return false;
        }
    }

    return true;
}

bool list_remove_element() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);
        auto it = list.begin();

        for (int j = 0; j < i; ++j) {
            if(j%2 == 0) {
                auto it2 = it;
                it2.next();

                list.remove(it);

                if(it2 != it) return false;
            } else it.next();
        }

        it = list.begin();
        auto end = list.end();
        int num = 1;
        while(it != end) {
            if(*it != num) return false;
            it.next();
            num += 2;
        }
    }

    return true;
}

bool list_swap() {
    for (int i = 0; i < 10; ++i) {
        auto list = create_list(i);
        auto it = list.begin();
        auto end = list.end();

        while(it != end) {
            auto it2 = it;

            it2.next();

            if(it2) list.swap(it, it2);

            it.next(); it.next();
        }

        it = list.begin();
        for (int j = 0; j < i-1; ++j, it.next()) {
            if(j%2 == 0) {
                if(*it != j+1) return false;
            } else {
                if(*it != j-1) return false;
            }
        }
    }

    return true;
}

bool list_sort() {
    std::random_device rd;
    std::mt19937 mt(rd());

    for (int i = 2; i < 10; ++i) {
        auto list = create_list(i);

        do {
            auto it = list.begin();
            auto end = list.end();

            // First, shuffle the list
            std::uniform_int_distribution<int> dist(0, i);
            while (it != end) {
                auto n = dist(mt);
                auto it2 = it;
                for (; n > 0; --n) it2.next();

                list.swap(it, it2);

                it.next();
            }

            // Second, make sure that it is really shuffled
        }while(is_ordered(list, i));

        // Third, sort the list
        list.sort();

        if(!is_ordered(list, i)) return false;
    }

    return true;
}

List<int> create_list(int cant) {
    List<int> list;

    for (int i = 0; i < cant; ++i) {
        list.add(i);
    }

    return list;
}

bool is_ordered(List<int> & list, int cant) {
    auto it = list.begin();
    auto end = list.end();
    int i = 0;
    while(it != end) {
        if(*it != i) return false;

        it.next();
        i++;
    }

    return i == cant;
}
