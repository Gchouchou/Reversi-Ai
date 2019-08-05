#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER
#include "board.h"
#include "coordinate.h"
#include "tree.h"

#include <mutex>

namespace MCT
{
    class tree;
} // namespace MCT


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
        MCT::tree *treeSearch;

        // update the window
        // if it's false we do a shallow update
        void updatecursor(const coordinate &c);
        void initializeTree();
    public:
        board getBoard() const {return currBoard;}
        void updatesuggested(const coordinate &c);
        void updateWin(bool updateType = true);
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