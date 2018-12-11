#include <algor/Point.hpp>
#include <istream>
#include <optional>

#include <test_cases/TestCasesLoader_impl/ParserShared.hpp>

namespace test_cases::__detail_TestCasesLoader {
    std::optional<algor::Point> parse_point(std::istream & input) {
        if(!input) return std::nullopt;

        int x, y;
        input >> x;

        if(!input) return std::nullopt;

        input >> y;

        return algor::Point(x, y);
    }
}
