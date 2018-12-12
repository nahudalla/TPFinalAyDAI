#ifndef TPFINALAYDAI_ALGOR_POINT_HPP
#define TPFINALAYDAI_ALGOR_POINT_HPP

#ifndef __EMSCRIPTEN__
#include <iostream>
#include <utility>
#endif

namespace algor {
    class Point {
        int x = 0, y = 0;

    public:
        Point() = default;

        Point(int x, int y) : x(x), y(y) {}

        Point(Point const &) = default;

        Point(Point &&) noexcept = default;

        Point &operator=(Point const &) = default;

        Point &operator=(Point &&) noexcept = default;

        ~Point() = default;

        int getX() const {
            return x;
        }

        int getY() const {
            return y;
        }

        bool operator==(const Point &rhs) const {
            return x == rhs.x &&
                   y == rhs.y;
        }

        bool operator!=(const Point &rhs) const {
            return !(rhs == *this);
        }

#ifndef __EMSCRIPTEN__
        friend std::ostream &operator<<(std::ostream & out, Point const& point) {
            return out << point.x << " " << point.y;
        }

        friend std::ostream &operator<<(std::ostream & out, std::pair<Point, Point> const& pair) {
            return out << pair.first << std::endl << pair.second;
        }
#endif
    };
}

#endif //TPFINALAYDAI_ALGOR_POINT_HPP
