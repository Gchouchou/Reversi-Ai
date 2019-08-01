#include "coordinate.h"
#include "game_settings.h"

using namespace reversi;

bool coordinate::shift(const direction dir) {
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