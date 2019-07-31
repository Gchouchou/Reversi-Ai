#ifndef COORDINATE_HEADER
#define COORDINATE_HEADER

namespace reversi
{
    struct coordinate
    {
        int x;
        int y;
        coordinate(int x, int y): x(x), y(y) {}
    };
} // namespace reversi


#endif