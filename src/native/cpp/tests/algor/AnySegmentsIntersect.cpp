#include "../Test.hpp"

#include <algor/List.hpp>
#include <algor/Segment.hpp>
#include <algor/AnySegmentsIntersect.hpp>

using namespace algor;

bool any_segments_intersect_instantiation(); ADD_TEST(ANY_SEGMENTS_INTERSECT_INSTANTIATION, any_segments_intersect_instantiation);
bool any_segments_intersect_non_intersecting_algorithm(); ADD_TEST(ANY_SEGMENTS_INTERSECT_NON_INTERSECTING_ALGORITHM, any_segments_intersect_non_intersecting_algorithm);
bool any_segments_intersect_intersecting_algorithm(); ADD_TEST(ANY_SEGMENTS_INTERSECT_INTERSECTING_ALGORITHM, any_segments_intersect_intersecting_algorithm);

List<Segment> generate_non_intersecting_segments();
List<Segment> generate_intersecting_segments();

bool any_segments_intersect_instantiation(List<Segment> const& list) {
    AnySegmentsIntersect algor(list);

    return true;
}
bool any_segments_intersect_instantiation() {
    for (int i = 0; i < 20; ++i) {
        any_segments_intersect_instantiation(generate_non_intersecting_segments());
        any_segments_intersect_instantiation(generate_intersecting_segments());
    }

    return true;
}

bool any_segments_intersect_algorithm(List<Segment> const& list, bool expected) {
    AnySegmentsIntersect algor(list);

    auto res = algor.run();

    if(!res.has_value()) return false;

    return res.value() == expected;
}
bool any_segments_intersect_non_intersecting_algorithm() {
    bool res = true;

    for (int i = 0; res && i < 20; ++i) {
        res = any_segments_intersect_algorithm(generate_non_intersecting_segments(), false);
    }

    return res;
}
bool any_segments_intersect_intersecting_algorithm() {
    bool res = true;

    for (int i = 0; res && i < 20; ++i) {
        res = any_segments_intersect_algorithm(generate_intersecting_segments(), true);
    }

    return res;
}

List<Segment> generate_non_intersecting_segments() {
    List<Segment> list;

    list.add(Segment(Point(-13, 5), Point(-7, 3)));
    list.add(Segment(Point(-10, 1), Point(-6, 2)));
    list.add(Segment(Point(-9, 5), Point(0, 1)));
    list.add(Segment(Point(-6, 5), Point(-1, 3)));
    list.add(Segment(Point(-3, 1), Point(-1, 0)));

    return std::move(list);
}

List<Segment> generate_intersecting_segments() {
    auto list = generate_non_intersecting_segments();

    list.add(Segment(Point(-11, -1), Point(1, 5)));

    return std::move(list);
}
