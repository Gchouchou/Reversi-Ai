#ifndef MOVE_HEADER
#define MOVE_HEADER
#include "coordinate.h"
#include "direction.h"

#include <forward_list>

namespace reversi {
    class board;

    class move
    {
    typedef std::forward_list<const direction> dirList;

    private:
        const coordinate position;
        // the one that was explored
        const direction mainDir;
        dirList *directions;

    public:
        const coordinate *getposition() const {return &position;}

        move(const coordinate &pos, const direction d) : position(pos),mainDir(d) {
            directions = nullptr;
        }
        ~move() {
            delete(directions);
        }

    friend bool operator==(const move &move1, const move &move2){
        return move1.position == move2.position;
    }

    friend class board;
    };
} // namespace reversi

#endif