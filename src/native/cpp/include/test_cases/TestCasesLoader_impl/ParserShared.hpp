#ifndef TPFINALAYDAI_TEST_CASES_PARSERSHARED_HPP
#define TPFINALAYDAI_TEST_CASES_PARSERSHARED_HPP

#include <algor/Point.hpp>
#include <istream>
#include <optional>

namespace test_cases::__detail_TestCasesLoader {
    std::optional<algor::Point> parse_point(std::istream & input);
}

#endif //TPFINALAYDAI_TEST_CASES_PARSERSHARED_HPP
