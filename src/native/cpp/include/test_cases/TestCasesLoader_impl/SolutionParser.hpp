#ifndef TPFINALAYDAI_TEST_CASES_SOLUTION_PARSER_HPP
#define TPFINALAYDAI_TEST_CASES_SOLUTION_PARSER_HPP

#include <utility>
#include <istream>
#include <optional>
#include <string>
#include <algorithm>

#include <algor/AnySegmentsIntersect.hpp>
#include <algor/GrahamScan.hpp>
#include <algor/JarvisMarch.hpp>
#include <algor/ClosestPairOfPoints.hpp>

#include <algor/List.hpp>
#include <algor/Stack.hpp>
#include <algor/Point.hpp>

#include <test_cases/TestCasesLoader_impl/ParserShared.hpp>

namespace test_cases::__detail_TestCasesLoader {
    template <typename Algorithm = void>
    struct SolutionParser;

    template <>
    struct SolutionParser<void> {
        typedef void SolutionType;
    };

    template <>
    struct SolutionParser<algor::AnySegmentsIntersect> {
        SolutionParser() = delete;

        typedef decltype(std::declval<algor::AnySegmentsIntersect>().run()) SolutionType;

        static SolutionType parseSolution(std::istream & input) {
            if(!input) return std::nullopt;

            std::string str;
            input >> str;
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);

            SolutionType res;

            if(str == "true" || str == "1") res = true;
            else if (str == "false" || str == "0") res = false;
            else res = std::nullopt;

            return res;
        }
    };

    template <>
    struct SolutionParser<algor::GrahamScan> {
        SolutionParser() = delete;

        typedef decltype(std::declval<algor::GrahamScan>().run()) SolutionType;

        static SolutionType parseSolution(std::istream & input) {
            algor::Stack<algor::Point> stack;

            std::optional<algor::Point> point = parse_point(input);

            while(point.has_value()) {
                stack.push(*point);
                point = parse_point(input);
            }

            if(!stack.isEmpty()) return std::move(stack);
            else return std::nullopt;
        }
    };

    template <>
    struct SolutionParser<algor::JarvisMarch> {
        SolutionParser() = delete;

        typedef SolutionParser<algor::GrahamScan>::SolutionType SolutionType;

        static SolutionType parseSolution(std::istream & input) {
            return SolutionParser<algor::GrahamScan>::parseSolution(input);
        }
    };

    template <>
    struct SolutionParser<algor::ClosestPairOfPoints> {
        SolutionParser() = delete;

        typedef decltype(std::declval<algor::ClosestPairOfPoints>().run()) SolutionType;

        static SolutionType parseSolution(std::istream & input) {
            auto p1 = parse_point(input),
                 p2 = parse_point(input);

            if(p1.has_value() && p2.has_value()) return std::make_pair(*p1, *p2);
            else return std::nullopt;
        }
    };
}

#endif //TPFINALAYDAI_TEST_CASES_SOLUTION_PARSER_HPP
