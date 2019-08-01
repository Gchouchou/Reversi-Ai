#ifndef DIRECTION_HEADER
#define DIRECTION_HEADER

namespace reversi {
    enum direction {
        downleft,
        down,
        downright,
        left,
        neutral,
        right,
        upleft,
        up,
        upright
    };
    // an array of all directions
    const direction dirs[] {
        downleft,
        down,
        downright,
        left,
        right,
        upleft,
        up,
        upright
    };
    inline direction flip(direction initial) {
        return (direction) (upright - initial);
    }
}
#endif