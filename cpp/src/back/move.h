#ifndef MOVE_HEADER
#define MOVE_HEADER
#include "coordinate.h"

#include <list>

namespace reversi {
    class board;

    class move
    {
    private:
        enum direction {
            up,
            down,
            left,
            right,
            upleft,
            upright,
            downleft,
            downright
        };
        const coordinate position;
        std::list<direction> directions;
        void addDirection(direction d); 
    public:
        const coordinate *getposition() const {return &position;}
        move(const coordinate &pos) : position(pos) {}
    friend class board;
    };
} // namespace reversi

#endif