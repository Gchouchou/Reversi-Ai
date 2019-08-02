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
        // to prevent too many updates
        std::mutex mutex;

        // update the window
        // if it's false we do a shallow update
        void updateWin(bool updateType = true);
    public:
        // take input from user
        bool input();

        gui();
        ~gui();
    };
} // namespace gui



#endif