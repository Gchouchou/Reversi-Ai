#ifndef MOVE_HEADER
#define MOVE_HEADER
#include "coordinate.h"
#include "direction.h"

#include <forward_list>

namespace reversi {
    class board;

    class move
    {
    typedef std::forward_list<direction> dirList;

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

        move(const move &copy):position(copy.position), mainDir(copy.mainDir){
            if (copy.directions != nullptr) {
                for (auto &&d : *copy.directions)
                {
                    directions->push_front(d);
                }
            } else
            {
                directions = nullptr;
            }
            
        }

    friend class board;
    };
} // namespace reversi

#endif