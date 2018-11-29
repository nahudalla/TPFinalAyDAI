#ifndef TPFINALAYDAI_SEGMENT_HPP
#define TPFINALAYDAI_SEGMENT_HPP

#include <algor/Point.hpp>
#include <algor/Vector.hpp>

namespace algor {
    class Segment {
        Point from, to;
    public:
        Segment(const Point &from, const Point &to) : from(from), to(to) {}

        const Point &getFrom() const {
            return from;
        }

        const Point &getTo() const {
            return to;
        }

        bool isClockwise(Segment const &rhs) const {
            if (this->from != rhs.from) return false;

            Vector v1(this->from, this->to), v2(rhs.from, rhs.to);

            return v1.isClockwise(v2);
        }

        bool isColinear(Segment const &rhs) const {
            if (this->from != rhs.from) return false;

            Vector v1(this->from, this->to), v2(rhs.from, rhs.to);

            return v1.isColinear(v2);
        }

        bool isCounterClockwise(Segment const &rhs) const {
            if (this->from != rhs.from) return false;

            Vector v1(this->from, this->to), v2(rhs.from, rhs.to);

            return v1.isCounterClockwise(v2);
        }

        bool turnsLeft(Segment const &rhs) const {
            if (this->to != rhs.from) return false;

            Vector v1(this->from, rhs.from), v2(this->from, rhs.to);

            return v1.isCounterClockwise(v2);
        }

        bool turnsRight(Segment const &rhs) const {
            if (this->to != rhs.from) return false;

            Vector v1(this->from, rhs.from), v2(this->from, rhs.to);

            return v1.isClockwise(v2);
        }

        bool intersects(Segment const &rhs) const {
            auto d1 = Vector(rhs.from, this->from).crossProduct(Vector(rhs.from, rhs.to));
            auto d2 = Vector(rhs.from, this->to).crossProduct(Vector(rhs.from, rhs.to));
            auto d3 = Vector(this->from, rhs.from).crossProduct(Vector(this->from, this->to));
            auto d4 = Vector(this->from, rhs.to).crossProduct(Vector(this->from, this->to));

            return (((d1 > 0 and d2 < 0) or (d1 < 0 and d2 > 0)) and ((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0)))
                   || (d1 == 0 and rhs.contains(this->from))
                   || (d2 == 0 and rhs.contains(this->to))
                   || (d3 == 0 and this->contains(rhs.from))
                   || (d4 == 0 and this->contains(rhs.to));
        }

        bool contains(Point point) const {
            return std::min(this->from.getX(), this->to.getX()) <= point.getX()
                   && point.getX() <= std::max(this->from.getX(), this->to.getX())
                   && std::min(this->from.getY(), this->to.getY()) <= point.getY()
                   && point.getY() <= std::max(this->from.getY(), this->to.getY());
        }
    };
}

#endif //TPFINALAYDAI_SEGMENT_HPP
