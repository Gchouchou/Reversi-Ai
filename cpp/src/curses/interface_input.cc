#include "interface.h"

#include <ncurses.h>

using namespace reversi;

bool gui::input() {
    // get the input
    int ch = getch();
    switch (ch)
    {
    case KEY_ENTER:
    case 10:
        // select move
        currBoard.playTurn(cursor);
        // full update
        currBoard.getValidMoves(validMoves);
        // multi thread...
        suggested = *validMoves[0];
        curIndex = 0;
        cursor = *validMoves[curIndex];
        updateWin();
        break;
    case 'n':
        curIndex = (curIndex + 1)%validMoves.size();
        cursor = *validMoves[curIndex];
        updateWin(false);
        break;
    case 'q':
        return false;
        break;
    }
    return true;
}
