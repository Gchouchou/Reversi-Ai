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
        int curIndex;
        // to prevent too many updates
        std::mutex mutex;

        // update the window
        // if it's false we do a shallow update
        void updateWin(bool updateType = true);
    public:
        // retun false when the game is over/or aborted
        // press n to go to next valid move
        // press enter to lock in move
        // press q to abort this returns true
        bool input();

        gui();
        ~gui();
    };
} // namespace gui



#endif