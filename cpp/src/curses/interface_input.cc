#include "interface.h"
#include "tree.h"

#include <ncurses.h>
#include <thread>

using namespace reversi;

void gui::initializeTree() {
    if (treeSearch == nullptr) {
        // initialize the tree and start searching
        treeSearch = new MCT::tree(*this,currBoard.getWho());
        std::thread th(&MCT::tree::startSearching,treeSearch);
        th.detach();
    }
}

bool gui::input() {
    // get the input
    int ch = getch();
    switch (ch)
    {
    case KEY_ENTER:
    case 10:
        if (treeSearch != nullptr) {
            treeSearch->setFlag();
            while (treeSearch->doneSearch() != true)
            ;
        }
        // select move
        currBoard.playTurn(cursor);
        // move down the tree
        if (treeSearch != nullptr)
        {
            treeSearch->chooseChild(cursor);
        }
        // full update
        currBoard.getValidMoves(validMoves);
        curIndex = 0;
        updatecursor(*validMoves[curIndex]);
        updateWin();
        // multi thread...
        if (treeSearch != nullptr) {
            std::thread th(&MCT::tree::startSearching,treeSearch);
            th.detach();
        }
        break;
    case KEY_UP:
    case KEY_RIGHT:
    case 'n':
        curIndex = (curIndex + 1)%validMoves.size();
        updatecursor(*validMoves[curIndex]);
        updateWin(false);
        break;
    case KEY_DOWN:
    case KEY_LEFT:
    case 'N':
        curIndex = (curIndex - 1)%validMoves.size();
        updatecursor(cursor = *validMoves[curIndex]);
        updateWin(false);
        break;
    case 'h':
        initializeTree();
        break;
    case 'q':
        // close the thread
        if (treeSearch != nullptr ) {
            treeSearch->setFlag();
            while (treeSearch->doneSearch() != true)
            ;
        }
        return false;
        break;
    }
    return true;
}

void gui::updatecursor(const coordinate &c) {
    // mutex for multi threading
    std::lock_guard<std::mutex> lockGuard(mutex);
    cursor = c;
}

void gui::updatesuggested(const coordinate &c) {
    // mutex for multi threading
    std::lock_guard<std::mutex> lockGuard(mutex);
    suggested = c;
}