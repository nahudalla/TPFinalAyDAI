#ifndef TPFINALAYDAI_TEST_CASES_TEST_CASE_PARSER_HPP
#define TPFINALAYDAI_TEST_CASES_TEST_CASE_PARSER_HPP

#include <utility>
#include <istream>
#include <optional>

#include <algor/AnySegmentsIntersect.hpp>
#include <algor/GrahamScan.hpp>
#include <algor/JarvisMarch.hpp>
#include <algor/ClosestPairOfPoints.hpp>
#include <algor/List.hpp>
#include <algor/Point.hpp>
#include <algor/Segment.hpp>

#include <test_cases/TestCasesLoader_impl/ParserShared.hpp>

namespace test_cases::__detail_TestCasesLoader {
    template <typename>
    struct TestCaseParser;

    template <>
    struct TestCaseParser<void> {
        typedef void TestCaseType;
    };

    template <>
    struct TestCaseParser<algor::AnySegmentsIntersect> {
        TestCaseParser() = delete;

        typedef algor::List<algor::Segment> TestCaseType;

        static TestCaseType parseTestCase(std::istream & input) {
            TestCaseType res;

            std::optional<algor::Point> from = parse_point(input),
                                        to = parse_point(input);

            while(from.has_value() && to.has_value()) {
                res.add(algor::Segment(*from, *to));

                from = parse_point(input);
                to = parse_point(input);
            }

            return std::move(res);
        }
    };

    template <>
    struct TestCaseParser<algor::GrahamScan> {
        TestCaseParser() = delete;

        typedef algor::List<algor::Point> TestCaseType;

        static TestCaseType parseTestCase(std::istream & input) {
            TestCaseType res;

            std::optional<algor::Point> point = parse_point(input);

            while(point.has_value()) {
                res.add(*point);
                point = parse_point(input);
            }

            return std::move(res);
        }
    };

    template <>
    struct TestCaseParser<algor::JarvisMarch> {
        TestCaseParser() = delete;

        typedef TestCaseParser<algor::GrahamScan>::TestCaseType TestCaseType;

        static TestCaseType parseTestCase(std::istream & input) {
            return TestCaseParser<algor::GrahamScan>::parseTestCase(input);
        }
    };

    template <>
    struct TestCaseParser<algor::ClosestPairOfPoints> {
        TestCaseParser() = delete;

        typedef algor::Array<algor::Point> TestCaseType;

        static TestCaseType parseTestCase(std::istream & input) {
            return algor::Array(TestCaseParser<algor::GrahamScan>::parseTestCase(input));
        }
    };
}

#endif //TPFINALAYDAI_TEST_CASES_TEST_CASE_PARSER_HPP
