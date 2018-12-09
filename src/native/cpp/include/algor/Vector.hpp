#ifndef TPFINALAYDAI_ALGOR_VECTOR_HPP
#define TPFINALAYDAI_ALGOR_VECTOR_HPP

#include <algor/Point.hpp>

namespace algor {
    class Vector : public Point {
    public:
        Vector(int x, int y) : Point(x, y) {}

        explicit Vector(Point &&point) : Point(point) {}

        explicit Vector(Point const &point) : Point(point) {}

        Vector(Point const &from, Point const &to) : Point(to.getX() - from.getX(), to.getY() - from.getY()) {}

        Vector(Vector const &) = default;

        Vector(Vector &&) noexcept = default;

        Vector &operator=(Vector const &) = default;

        Vector &operator=(Vector &&) noexcept = default;

        ~Vector() = default;

        int crossProduct(Vector const &rhs) const {
            return (this->getX() * rhs.getY()) - (rhs.getX() * this->getY());
        }

        bool isClockwise(Vector const &rhs) const {
            return rhs.crossProduct(*this) > 0;
        }

        bool isColinear(Vector const &rhs) const {
            return rhs.crossProduct(*this) == 0;
        }

        bool isCounterClockwise(Vector const &rhs) const {
            return rhs.crossProduct(*this) < 0;
        }
    };
}

algor::Vector operator-(algor::Point const& lhs, algor::Point const& rhs);

#endif //TPFINALAYDAI_ALGOR_VECTOR_HPP
