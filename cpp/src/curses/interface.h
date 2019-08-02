#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER
#include "board.h"
#include "coordinate.h"

#include <mutex>

namespace reversi
{
    class gui
    {
    private:
        // data members
        board currBoard;
        coordinate cursor;
        coordinate suggested;
        validMoveList validMoves;
        // if it's false we do a shallow update
        bool updateType;
        // to prevent too many updates
        std::mutex mutex;

        // update the window
        void updateWin();
    public:
        // take input from user
        void input();

        gui();
        ~gui();
    };
} // namespace gui



#endif