#include "../Test.hpp"

#include <algor/List.hpp>
#include <algor/Stack.hpp>
#include <algor/Point.hpp>
#include <algor/GrahamScan.hpp>

#include <sstream>

using namespace algor;

bool graham_scan_instantiate(); ADD_TEST(GRAHAM_SCAN_INSTANTIATE, graham_scan_instantiate);
bool graham_scan_algorithm(); ADD_TEST(GRAHAM_SCAN_ALGORITHM, graham_scan_algorithm);

std::stringstream get_test_points_string();
std::stringstream  get_solution_points_string();
List<Point> generate_test_points_list();
Stack<Point> generate_solution_points_stack();

bool graham_scan_instantiate() {
    for (int i = 0; i < 0; ++i) {
        GrahamScan gs(generate_test_points_list());

        if(!gs.canRun() || gs.hasResult()) return false;
    }

    return true;
}

bool graham_scan_algorithm() {
    for (int i = 0; i < 1; ++i) {
        GrahamScan gs(generate_test_points_list());

        auto res = gs.run();

        if(!res.has_value()) return false;

        auto solution = generate_solution_points_stack();

        while(!solution.isEmpty() && !res->isEmpty()) {
            if(solution.pop() != res->pop()) return false;
        }
    }

    return true;
}

List<Point> generate_test_points_list() {
    List<Point> list;

    auto ss = get_test_points_string();

    int x, y;

    while(ss >> x >> y) {
        list.add(Point(x, y));
    }

    return std::move(list);
}

Stack<Point> generate_solution_points_stack() {
    Stack<Point> stack;

    auto ss = get_solution_points_string();

    int x, y;

    while(ss >> x >> y) {
        stack.push(Point(x, y));
    }

    return std::move(stack);
}

std::stringstream get_test_points_string() {
    return std::stringstream(
            "4 10\n"
            "6 10\n"
            "14 14\n"
            "10 4\n"
            "4 6\n"
            "10 10\n"
            "8 12\n"
            "2 16\n"
            "2 10\n"
            "6 6\n"
            "14 6\n"
            "12 12\n"
            "4 14\n"
            "10 16\n"
            "14 18\n"
            "8 20\n"
            "14 8\n"
   );
}

std::stringstream get_solution_points_string() {
    return std::stringstream(
            "10 4\n"
            "14 6\n"
            "14 18\n"
            "8 20\n"
            "2 16\n"
            "2 10\n"
            "4 6\n"
    );
}