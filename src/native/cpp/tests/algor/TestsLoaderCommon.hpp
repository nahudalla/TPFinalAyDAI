#ifndef TPFINALAYDAI_TESTSLOADERCOMMON_HPP
#define TPFINALAYDAI_TESTSLOADERCOMMON_HPP

#include <test_cases/TestCasesLoader.hpp>

template <typename Algorithm>
auto * & __getLoaderPointer() {
    static const test_cases::TestCasesLoader<Algorithm> * TESTS_LOADER = nullptr;

    return TESTS_LOADER;
}

template <typename Algorithm>
const auto & getTestsLoader() {
    auto * & TESTS_LOADER = __getLoaderPointer<Algorithm>();

    if(TESTS_LOADER == nullptr) {
        TESTS_LOADER = new test_cases::TestCasesLoader<Algorithm>();
    }

    return *TESTS_LOADER;
}

template <typename Algorithm>
bool cleanupTestsLoader() {
    auto * & TESTS_LOADER = __getLoaderPointer<Algorithm>();

    if(TESTS_LOADER != nullptr) {
        delete TESTS_LOADER;
        TESTS_LOADER = nullptr;
    }

    return true;
}

#endif //TPFINALAYDAI_TESTSLOADERCOMMON_HPP
