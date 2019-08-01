#ifndef COORDINATE_HEADER
#define COORDINATE_HEADER
#include "direction.h"

namespace reversi
{
    struct coordinate
    {
        int x;
        int y;
        // shift x and y according to direction
        bool shift(const direction dir);
        coordinate(const int x, const int y): x(x), y(y) {}
        coordinate() {}
        // simple == operator
        friend bool operator==(const coordinate &a, const coordinate &b) {
            return a.x == b.x && a.y == b.y;
        }
    };
} // namespace reversi


#endif