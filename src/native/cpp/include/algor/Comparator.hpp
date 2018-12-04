#ifndef TPFINALAYDAI_COMPARATOR_HPP
#define TPFINALAYDAI_COMPARATOR_HPP

namespace algor {
    template <typename T>
    class Comparator {
    public:
        virtual int compare(T const& lhs, T const& rhs) const {
            return (lhs < rhs) ? -1 : ((rhs < lhs) ? 1 : 0);
        }
    };
}

#endif //TPFINALAYDAI_COMPARATOR_HPP
