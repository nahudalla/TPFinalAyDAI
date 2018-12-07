#ifndef TPFINALAYDAI_ANYSEGMENTSINTERSECT_HPP
#define TPFINALAYDAI_ANYSEGMENTSINTERSECT_HPP

#include <optional>
#include <tuple>

#include <algor/List.hpp>
#include <algor/Segment.hpp>
#include <algor/RBTree.hpp>
#include <algor/Comparator.hpp>

namespace algor {
    class AnySegmentsIntersect {
        enum Position {LEFT, RIGHT};
        enum Which {FROM, TO};

        typedef std::tuple<Segment, Which, Position> Endpoint;

        static const auto & getComparator() {
            typedef Comparator<Endpoint> TCmp;

            static const TCmp endpoint_comparator =
                    (TCmp::ComparatorFunction) [](const Endpoint & lhs, const Endpoint & rhs) -> int {
                const auto EQUALS = 0;
                const auto RIGHT_BIGGER = -1;
                const auto LEFT_BIGGER = 1;

                const auto & segment1 = std::get<0>(lhs);
                const auto & segment2 = std::get<0>(rhs);

                const auto & which1 = std::get<1>(lhs);
                const auto & which2 = std::get<1>(rhs);

                const auto & pos1 = std::get<2>(lhs);
                const auto & pos2 = std::get<2>(rhs);

                auto & point1 = (which1 == FROM) ? segment1.getFrom() : segment1.getTo();
                auto & point2 = (which2 == FROM) ? segment2.getFrom() : segment2.getTo();

                if(point1.getX() == point2.getX()) {
                    if(pos1 == pos2) {
                        return point1.getY() == point2.getY() ? EQUALS :
                                (point1.getY() < point2.getY() ? RIGHT_BIGGER : LEFT_BIGGER);
                    } else if(pos1 == LEFT && pos2 == RIGHT) return RIGHT_BIGGER;
                    else return LEFT_BIGGER;
                } else if(point1.getX() < point2.getX()) return RIGHT_BIGGER;
                else return LEFT_BIGGER;
            };

            return endpoint_comparator;
        }

        std::optional<bool> result;
        std::optional<List<Endpoint>> endpoints;
    public:
        explicit AnySegmentsIntersect(List<Segment> const& segments) {
            // Preparo los puntos para luego ser procesados
            auto it = segments.cbegin();
            auto end = segments.cend();

            this->endpoints = List<Endpoint>();

            for(; it != end; ++it) {
                const Segment & segment = *it;
                const Point & from = segment.getFrom();
                const Point & to = segment.getTo();

                if(from.getX() == to.getX()) continue; // PRECONDICIÓN: no puede haber segmentos verticales

                if(from.getX() < to.getX()) {
                    endpoints->add(Endpoint(segment, FROM, LEFT));
                    endpoints->add(Endpoint(segment, TO, RIGHT));
                } else {
                    endpoints->add(Endpoint(segment, FROM, RIGHT));
                    endpoints->add(Endpoint(segment, TO, LEFT));
                }
            }

            if(this->endpoints->isEmpty()) {
                this->endpoints.reset();
            } else {
                this->endpoints->sort(AnySegmentsIntersect::getComparator());
            }
        }

        // TODO: implement rest of algorithm
    };
}

#endif //TPFINALAYDAI_ANYSEGMENTSINTERSECT_HPP
