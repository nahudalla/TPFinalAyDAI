#include "../Test.hpp"

#include <algor/Array.hpp>

using namespace algor;

bool array_initializer_list(); ADD_TEST(ARRAY_INITIALIZER_LIST, array_initializer_list);
bool array_size(); ADD_TEST(ARRAY_SIZE, array_size);
bool array_subscript_operator(); ADD_TEST(ARRAY_SUBSCRIPT_OPERATOR, array_subscript_operator);

Array<int> create_array(std::size_t size);

bool array_initializer_list() {
    Array<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    return true;
}

bool array_subscript_operator() {
    for (std::size_t i = 1; i < 20; ++i) {
        auto array = create_array(i);

        for(auto j = i; j > 0; --j) {
            if(array[j-1] != j-1) return false;
        }
    }

    return true;
}

bool array_size() {
    for (int i = 0; i < 20; ++i) {
        auto arr = create_array(i);

        if(arr.size() != i) return false;
    }

    return true;
}

Array<int> create_array(std::size_t size) {
    Array<int> array(size);
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }

    return std::move(array);
}
