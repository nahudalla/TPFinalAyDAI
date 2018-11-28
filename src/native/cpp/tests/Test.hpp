#ifndef TESTS_TEST_HPP
#define TESTS_TEST_HPP

#include <functional>
#include <list>
#include <string>

namespace Tests {
    struct Test {
        std::string name;
        std::function<bool()> test;

        Test(std::string name, std::function<bool()> test);

        static std::list<Test> tests;
    };
}

#define ADD_TEST(name, def) \
struct Test_ ## name {\
    static char _init;\
    static char init() noexcept { \
        try{Tests::Test::tests.emplace_back(::Tests::Test(#name, (def)));}catch(...){} \
        return ' '; \
    } \
}; \
char Test_ ## name::_init = Test_ ## name::init()

#endif //TESTS_TEST_HPP