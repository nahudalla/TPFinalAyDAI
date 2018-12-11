#ifndef TPFINALAYDAI_TESTCASESLOADER_HPP
#define TPFINALAYDAI_TESTCASESLOADER_HPP

#include <iostream>

#include <type_traits>
#include <fstream>
#include <experimental/filesystem>

#include <test_cases/TestCasesLoader_impl/SolutionDirNames.hpp>
#include <test_cases/TestCasesLoader_impl/TestCaseParser.hpp>
#include <test_cases/TestCasesLoader_impl/SolutionParser.hpp>

#include <algor/List.hpp>

namespace fs = std::experimental::filesystem;

namespace test_cases {
#ifndef DEBUG
    static constexpr const char * DEFAULT_TEST_CASES_DIRECTORY = "./test_cases";
#else
    static constexpr const char * DEFAULT_TEST_CASES_DIRECTORY = "../test_cases";
#endif

    template <typename Algorithm>
    class TestCasesLoader {
        using TestCaseParser = __detail_TestCasesLoader::TestCaseParser<Algorithm>;
        using SolutionParser = __detail_TestCasesLoader::SolutionParser<Algorithm>;

        using TestCaseType = typename TestCaseParser::TestCaseType;
        using SolutionType = typename SolutionParser::SolutionType::value_type;

        static constexpr const char * SOLUTIONS_DIR_NAME = __detail_TestCasesLoader::SolutionDirName<Algorithm>::DIR_NAME;

        static_assert(
                !std::is_same_v<TestCaseType , void>
                && !std::is_same_v<SolutionType , void>
                && SOLUTIONS_DIR_NAME != nullptr
                , "Unrecognized algorithm type!"
        );

        algor::List<TestCaseType> test_cases;
        algor::List<SolutionType> solutions;

    public:
        explicit TestCasesLoader(const char * directory) {
            if(directory == nullptr) directory = DEFAULT_TEST_CASES_DIRECTORY;

            fs::path dir_path(directory);

            if(!fs::exists(dir_path)) {
                std::cerr << "ERROR: Test case directory does not exist!: " << directory;
                return;
            }

            for (auto & p : fs::directory_iterator(directory)) {
                const auto & test_case_path = p.path();
                if(!fs::is_regular_file(p) || test_case_path.extension().compare(".txt") != 0) continue;

                fs::path solution_path = test_case_path.parent_path() / SOLUTIONS_DIR_NAME / test_case_path.stem() . concat(".sol.txt");

                if(!fs::exists(solution_path)) continue;

                std::ifstream test_case_file(test_case_path);
                std::ifstream solution_file(solution_path);

                auto test_case = TestCaseParser::parseTestCase(test_case_file);
                auto solution = SolutionParser::parseSolution(solution_file);

                test_case_file.close();
                solution_file.close();

                if(!solution) continue;

                this->test_cases.add(std::move(test_case));
                this->solutions.add(std::move(*solution));
            }
        }

        TestCasesLoader() : TestCasesLoader(DEFAULT_TEST_CASES_DIRECTORY)
        {}

        TestCasesLoader(TestCasesLoader &&) noexcept = default;
        TestCasesLoader &operator=(TestCasesLoader &&) noexcept = default;
        TestCasesLoader(TestCasesLoader const&) = default;
        TestCasesLoader &operator=(TestCasesLoader const&) = default;
        ~TestCasesLoader() = default;

        const auto & getTestCases() const {
            return this->test_cases;
        }

        const auto & getSolutions() const {
            return this->solutions;
        }
    };
}

#endif //TPFINALAYDAI_TESTCASESLOADER_HPP
