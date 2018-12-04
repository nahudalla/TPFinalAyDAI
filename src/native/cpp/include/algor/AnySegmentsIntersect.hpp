#ifndef TPFINALAYDAI_ANYSEGMENTSINTERSECT_HPP
#define TPFINALAYDAI_ANYSEGMENTSINTERSECT_HPP

#include <optional>

#include <algor/List.hpp>
#include <algor/Segment.hpp>
#include <algor/RBTree.hpp>

namespace algor {
    class AnySegmentsIntersect {
        enum Position {LEFT, RIGHT};

        typedef std::tuple<Segment, Position> Endpoint;

        std::optional<bool> result;


    public:
        explicit AnySegmentsIntersect(List<Segment> const& segments) {
            // TODO: implement algorithm
        }
    };
}

#endif //TPFINALAYDAI_ANYSEGMENTSINTERSECT_HPP
