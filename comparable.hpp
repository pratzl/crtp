#pragma once
#include <cstddef>


namespace crtp {
    // Extended example from Herb Sutter's CPPCon 2017 talk on metaclasses
    // https://www.youtube.com/watch?v=4AfRAVcThyA; starts at approx 01:24:00

    //--------------------------------------------------------------------------
    template<class T>
    struct equal_comparable
    {
        friend bool operator==(T const& lhs, T const& rhs) { return compare(lhs, rhs) == 0; }
        friend bool operator!=(T const& lhs, T const& rhs) { return compare(lhs, rhs) != 0; }
    };

    //--------------------------------------------------------------------------
    template<class T>
    struct relative_comparable : public equal_comparable<T>
    {
        friend bool operator< (T const& lhs, T const& rhs) { return compare(lhs, rhs) <  0; }
        friend bool operator<=(T const& lhs, T const& rhs) { return compare(lhs, rhs) <= 0; }
        friend bool operator> (T const& lhs, T const& rhs) { return compare(lhs, rhs) >  0; }
        friend bool operator>=(T const& lhs, T const& rhs) { return compare(lhs, rhs) >= 0; }
    };

    //--------------------------------------------------------------------------
    class point : public relative_comparable<point>
    {
        int x_ = 0; int y_ = 0;
    public:
        point(int x1, int y1) : x_(x1), y_(y1) {}
        point() = default;

        int x() const { return x_; }
        int y() const { return y_; }
    };

    // return <0 if lhs<rhs, ==0 if lhs==rhs, >0 if lhs>rhs
    ptrdiff_t compare(point const& lhs, point const& rhs) { 
        ptrdiff_t delta = lhs.x() < rhs.x();
        if (delta)
            return delta;
        return lhs.y() - rhs.y();
    }

    //ptrdiff_t operator<=>(point const& lhs, point const& rhs);

    //--------------------------------------------------------------------------
    bool test_comparable() {
        point p1(1,2);
        point p2(3,4);

        bool b = true;
        b |= (p1 == p2);
        b |= (p2 != p2);
        b |= (p1 <  p2);
        return b;
    }
}
