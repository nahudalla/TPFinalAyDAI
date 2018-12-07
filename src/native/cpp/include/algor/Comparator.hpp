#ifndef TPFINALAYDAI_COMPARATOR_HPP
#define TPFINALAYDAI_COMPARATOR_HPP

#include <functional>

namespace algor {
    template <typename T>
    class Comparator final {
    public:
        typedef std::function<int(const T &, const T &)> ComparatorFunction;

    private:
        ComparatorFunction comparatorFunction = [](const T & lhs, const T & rhs) -> int {
            return (lhs < rhs) ? -1 : ((rhs < lhs) ? 1 : 0);
        };

    public:
        Comparator(ComparatorFunction comparatorFunction)
            : comparatorFunction(std::move(comparatorFunction))
        {}
        Comparator &operator=(ComparatorFunction const& rhs) {
            if(this != &rhs) {
                this->comparatorFunction = rhs;
            }

            return *this;
        }
        Comparator &operator=(ComparatorFunction && rhs) noexcept {
            if(this != &rhs) {
                this->comparatorFunction = std::move(rhs);
            }

            return *this;
        }

        Comparator() = default;
        Comparator(Comparator const&) = default;
        Comparator(Comparator &&) noexcept = default;
        Comparator &operator=(Comparator const&) = default;
        Comparator &operator=(Comparator &&) noexcept = default;
        ~Comparator() = default;

        int compare(const T & lhs, const T & rhs) const {
            return this->comparatorFunction(lhs, rhs);
        }
    };
}

#endif //TPFINALAYDAI_COMPARATOR_HPP
