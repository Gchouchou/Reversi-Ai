#ifndef COORDINATE_HEADER
#define COORDINATE_HEADER
#include "direction.h"
#include "game_settings.h"

namespace reversi
{
    struct coordinate
    {
        int x;
        int y;
        // shift x and y according to direction
        inline bool shift(const direction dir) {
            // from design
            int xshift = dir%3 - 1;
            int yshift = dir/3 - 1;
            if (x+xshift >= 0 && y + yshift >= 0 && x+xshift < BOARD_SIDE_LENGTH && \
            y+yshift < BOARD_SIDE_LENGTH)
            {
                x+=xshift;
                y+=yshift;
                return true;
            }
            else
            {
                return false;
            }
        }
        coordinate(const int x, const int y): x(x), y(y) {}
        coordinate() {}
        // simple == operator
        friend bool operator==(const coordinate &a, const coordinate &b) {
            return a.x == b.x && a.y == b.y;
        }
    };
} // namespace reversi


#endif