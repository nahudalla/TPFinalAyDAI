#ifndef TPFINALAYDAI_ALGOR_POINT_HPP
#define TPFINALAYDAI_ALGOR_POINT_HPP

namespace algor {
    class Point {
        int x, y;

    public:
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
    };
}

#endif //TPFINALAYDAI_ALGOR_POINT_HPP
